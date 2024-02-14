#include "HTMLParseTagState.h"

#include <PunctuationToken.h>
#include <LexingTools.h>

#include "HTMLParser.h"
#include "HTMLParseGenericState.h"
#include "HTMLParseCommentState.h"

HTMLParseTagState::HTMLParseTagState()
{
	counter = 0;
	is_closing_tag = false;
	parsing_attribute_value = false;
	parsing_attribute_name = false;
}

unique_ptr<Token> HTMLParseTagState::scan(unique_ptr<Token> token)
{
	auto parser = (HTMLParser*)machine;
	auto currentNodePtr = parser->current_node.lock();
	// On the first run, we determine if this is a closing
	// or an opening tag
	if (counter == 0)
	{
		if (token->type == StdTokenType::punctuation)
		{
			auto pToken = (PunctuationToken*)token.get();
			if (pToken->value == "/")
			{
				is_closing_tag = true;
			}
		}
		if (!is_closing_tag)
		{
			// Create a new element
			auto el = shared_ptr<HTMLNode>(HTMLNode::element());
			currentNodePtr->append_child(el);
			parser->current_node = el;
			currentNodePtr = parser->current_node.lock();
		}
	}
	if (token->type == StdTokenType::str)
	{
		auto sToken = (StringToken*)token.get();
		if (currentNodePtr->tag_name.empty() || currentNodePtr->tag_name == "!")
		{
			currentNodePtr->tag_name += sToken->value;
		}
		else if (is_closing_tag && closing_tag_name.empty())
		{
			closing_tag_name += sToken->value;
		}
		else
		{
			if (!is_closing_tag)
			{
				if (parsing_attribute_value)
				{
					currentNodePtr->attributes[attribute_name] = sToken->value;
					parsing_attribute_value = false;
					apply_attribute_name();
				}
				else
				{
					// This should be the left hand side of an attribute,
					// but there could be more to the attribute name.
					// Example: data-name
					// = string token, punctuation token, string token
					attribute_name += sToken->value;
					parsing_attribute_name = true;
				}
			}
		}
	}
	else if (token->type == StdTokenType::whitespace)
	{
		// In the case we have something such as
		// data- day="123"
		// it should be parsed as two attributes
		if (parsing_attribute_name)
		{
			parsing_attribute_name = false;
		}
	}
	else if (token->type == StdTokenType::punctuation)
	{
		auto pToken = (PunctuationToken*)token.get();
		if (pToken->value == "!")
		{
			// Maybe !DOCTYPE
			if (counter == 0)
			{
				currentNodePtr->tag_name = "!";
			}
		}
		else if (pToken->value == ">")
		{
			apply_attribute_name();
			if (currentNodePtr->is_void_element())
			{
				// Void elements just make the current node the parent node again
				auto parentNodePtr = currentNodePtr->parent_node.lock();
				if (parentNodePtr)
				{
					parser->current_node = parentNodePtr;
				}
			}
			else if (is_closing_tag)
			{
				// what tag name was the closing tag actually for?
				// Traverse the tree upwards, looking for a matching tag
				// name with end_tag_found set to false. If not found,
				// Do absolutely nothing (mismatched tag!)
				auto openingTagPtr = find_opening_tag(closing_tag_name);
				if (openingTagPtr)
				{
					openingTagPtr->closing_tag_found = true;
					parser->current_node = openingTagPtr->parent_node.lock();
				}
			}
			transition(new HTMLParseGenericState());
		}
		else if (pToken->value == "-")
		{
			if (counter == 1 && currentNodePtr->tag_name == "!")
			{
				// Is this a comment...?
				currentNodePtr->tag_name += "-";
			}
			else if (counter == 2 && currentNodePtr->tag_name == "!-")
			{
				// This is a comment!
				currentNodePtr->tag_name = "";
				currentNodePtr->type = HTMLNodeType::Comment;
				transition(new HTMLParseCommentState());
			}
			else
			{
				if (parsing_attribute_name)
				{
					attribute_name += "-";
				}
			}
		}
		else if (pToken->value == "=")
		{
			if (!is_closing_tag)
			{
				if (!attribute_name.empty())
				{
					// We are no longer parsing the lhs of the attribute
					// syntax
					parsing_attribute_name = false;
					if (parsing_attribute_value)
					{
						// Double equals sign will be interpreted as the value of this
						// attribute is literally an equals sign.
						currentNodePtr->attributes[attribute_name] = "=";
						parsing_attribute_value = false;
						attribute_name.clear();
					}
					else
					{
						// We have an attribute_name in the chamber,
						// now we have seen an "=",
						// so the next thing should be the value
						parsing_attribute_value = true;
					}
				}
			}
		}
	}
	counter++;
	return nullptr;
}

void HTMLParseTagState::apply_attribute_name()
{
	if (!attribute_name.empty())
	{
		auto parser = (HTMLParser*)machine;
		auto currentNodePtr = parser->current_node.lock();
		if (!currentNodePtr->attributes.contains(attribute_name))
		{
			currentNodePtr->attributes[attribute_name] = "";
		}
		attribute_name.clear();
		parsing_attribute_name = false;
	}
}

shared_ptr<HTMLNode> HTMLParseTagState::find_opening_tag(string_view tag_name)
{
	auto parser = (HTMLParser*)machine;
	auto currentSearchNode = parser->current_node.lock();

	while (currentSearchNode)
	{
		//                             Don't scan root element
		if (currentSearchNode->type == HTMLNodeType::Element &&
			!currentSearchNode->closing_tag_found &&
			LexingTools::compare_case_insensitive(tag_name, currentSearchNode->tag_name))
		{
			return currentSearchNode;
		}
		currentSearchNode = currentSearchNode->parent_node.lock();
	}

	return nullptr;
}

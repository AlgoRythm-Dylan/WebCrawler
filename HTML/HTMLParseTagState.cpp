#include "HTMLParseTagState.h"

#include <PunctuationToken.h>

#include "HTMLParser.h"
#include "HTMLParseGenericState.h"
#include "HTMLParseCommentState.h"
#include "HTMLNode.h"

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
			parser->current_node->append_child(el);
			parser->current_node = el;
		}
	}
	if (token->type == StdTokenType::str)
	{
		auto sToken = (StringToken*)token.get();
		if (parser->current_node->tag_name.empty() || parser->current_node->tag_name == "!")
		{
			parser->current_node->tag_name += sToken->value;
		}
		else
		{
			if (!is_closing_tag)
			{
				if (parsing_attribute_value)
				{
					parser->current_node->attributes[attribute_name] = sToken->value;
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
				parser->current_node->tag_name = "!";
			}
		}
		else if (pToken->value == ">")
		{
			apply_attribute_name();
			if (parser->current_node->is_void_element() || is_closing_tag)
			{
				if (parser->current_node->parent_node)
				{
					parser->current_node = parser->current_node->parent_node;
				}
			}
			transition(new HTMLParseGenericState());
		}
		else if (pToken->value == "-")
		{
			if (counter == 1 && parser->current_node->tag_name == "!")
			{
				// Is this a comment...?
				parser->current_node->tag_name += "-";
			}
			else if (counter == 2 && parser->current_node->tag_name == "!-")
			{
				// This is a comment!
				parser->current_node->tag_name = "";
				parser->current_node->type = HTMLNodeType::Comment;
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
						parser->current_node->attributes[attribute_name] = "=";
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
		if (!parser->current_node->attributes.contains(attribute_name))
		{
			parser->current_node->attributes[attribute_name] = "";
		}
		attribute_name.clear();
		parsing_attribute_name = false;
	}
}
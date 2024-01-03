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
		if (parser->current_node->tag_name.empty() || parser->current_node->tag_name == "!")
		{
			auto sToken = (StringToken*)token.get();
			parser->current_node->tag_name += sToken->value;
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
		}
	}
	counter++;
	return nullptr;
}
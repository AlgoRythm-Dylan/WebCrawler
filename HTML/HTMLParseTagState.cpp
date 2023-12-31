#include "HTMLParseTagState.h"

#include <PunctuationToken.h>

#include "HTMLParser.h"
#include "HTMLNode.h"

HTMLParseTagState::HTMLParseTagState()
{
	counter = 0;
}

unique_ptr<Token> HTMLParseTagState::scan(unique_ptr<Token> token)
{
	auto parser = (HTMLParser*)machine;
	if (token->type == StdTokenType::str)
	{
		if (parser->current_node->tag_name.empty() || parser->current_node->tag_name == "!")
		{
			parser->current_node->tag_name += ((StringToken*)token.get())->value;
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
			if (parser->current_node->is_void_element())
			{
				if (parser->current_node->parent_node)
				{
					parser->current_node = parser->current_node->parent_node;
				}
			}
		}
	}
	counter++;
	return nullptr;
}
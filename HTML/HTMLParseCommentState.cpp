#include "HTMLParseCommentState.h"

#include <PunctuationToken.h>

#include "HTMLParseGenericState.h"
#include "HTMLParser.h"

HTMLParseCommentState::HTMLParseCommentState()
{
	consecutive_dash_count = 0;
}

unique_ptr<Token> HTMLParseCommentState::scan(unique_ptr<Token> token)
{
	auto parser = (HTMLParser*)machine;
	if (token->type == StdTokenType::punctuation)
	{
		auto pToken = (PunctuationToken*)token.get();
		if (pToken->value == "-")
		{
			consecutive_dash_count++;
		}
		else
		{
			if (consecutive_dash_count > 0)
			{
				// Those dashes were not part of the end comment sequence
				// and therefore need to be added to the node as text content
				parser->current_node->text_content += string(consecutive_dash_count, '-');
			}
			if (pToken->value == ">")
			{
				if (consecutive_dash_count >= 2)
				{
					// That's it boys, the comment's over. Wrap it up.
					//
					// The comment **may** end with more than two dashes.
					// if it does, add them to the end of the text content
					// of this node
					if (consecutive_dash_count > 2)
					{
						parser->current_node->text_content += string(consecutive_dash_count - 2, '-');
					}
					parser->current_node = parser->current_node->parent_node;
					transition(new HTMLParseGenericState());
				}
			}
			else
			{
				parser->current_node->text_content += pToken->value;
			}
			consecutive_dash_count = 0;
		}
	}
	else
	{
		consecutive_dash_count = 0;
	}

	if (token->type == StdTokenType::str)
	{
		parser->current_node->text_content += ((StringToken*)token.get())->value;
	}
	return nullptr;
}
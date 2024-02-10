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
						auto currentNodePtr = parser->current_node.lock();
						currentNodePtr->text_content += string(consecutive_dash_count - 2, '-');
					}
					auto currentNodePtr = parser->current_node.lock();
					auto currentNodeParentPtr = currentNodePtr->parent_node.lock();
					parser->current_node = currentNodeParentPtr;
					transition(new HTMLParseGenericState());
				}
			}
			else
			{
				auto currentNodePtr = parser->current_node.lock();
				currentNodePtr->text_content += pToken->value;
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
		auto currentNodePtr = parser->current_node.lock();
		currentNodePtr->text_content += ((StringToken*)token.get())->value;
	}
	return nullptr;
}
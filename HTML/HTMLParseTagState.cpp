#include "HTMLParseTagState.h"

#include <PunctuationToken.h>

#include "HTMLParser.h"
#include "HTMLElement.h"

HTMLParseTagState::HTMLParseTagState()
{
	counter = 0;
}

unique_ptr<Token> HTMLParseTagState::scan(unique_ptr<Token> token)
{
	auto parser = (HTMLParser*)machine;
	auto currentTag = (HTMLElement*)(parser->current_node.get());
	if (token->type == StdTokenType::str)
	{
		if (currentTag->tag_name.empty() || currentTag->tag_name == "!")
		{
			currentTag->tag_name += ((StringToken*)token.get())->value;
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
				currentTag->tag_name = "!";
			}
		}
		else if (pToken->value == ">")
		{
			if (currentTag->is_void_element())
			{
				if (currentTag->parent_node)
				{
					parser->current_node = currentTag->parent_node;
				}
			}
		}
	}
	counter++;
	return nullptr;
}
#include <PunctuationToken.h>

#include "UrlParseAuthorityState.h"

unique_ptr<Token> UrlParseAuthorityState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::str)
	{
		memory.push_back(token);
	}
	else if (token->type == StdTokenType::punctuation)
	{
		auto puncToken = (PunctuationToken*)token.get();
		if (puncToken->value == "/")
		{

		}
	}
	else if (token->type == StdTokenType::end)
	{

	}
}
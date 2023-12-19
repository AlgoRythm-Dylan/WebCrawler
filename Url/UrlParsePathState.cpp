#include "UrlParsePathState.h"

#include <PunctuationToken.h>

unique_ptr<Token> UrlParsePathState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::punctuation)
	{
		auto pToken = (PunctuationToken*)token.get();
		if (pToken->value == "?")
		{
			// Transition to query parsing state
			return std::move(token);
		}
		else
		{
			memory += pToken->value;
		}
	}
	else if (token->type == StdTokenType::str)
	{
		auto sToken = (StringToken*)token.get();
		memory += sToken->value;
	}
	return nullptr;
}
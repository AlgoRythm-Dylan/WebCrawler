#include <PunctuationToken.h>

#include "UrlParseAuthorityState.h"

unique_ptr<Token> UrlParseAuthorityState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::str)
	{
		memory.push_back(std::move(token));
	}
	else if (token->type == StdTokenType::punctuation)
	{
		auto puncToken = (PunctuationToken*)token.get();
		if (puncToken->value == "/")
		{
			finish();
			// TODO: transition to path parse state
		}
	}
	else if (token->type == StdTokenType::end)
	{

	}
	return nullptr;
}

/*
	This state keeps a rather large memory
	because there is plenty of shared punctuation
	such as : for user:pass and : for port.
	At the end, after everything was loaded into
	memory, we put the puzle pieces together
*/
void UrlParseAuthorityState::finish()
{

}
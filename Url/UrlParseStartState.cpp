#include <PunctuationToken.h>
#include <StringToken.h>

#include "UrlParseStartState.h"
#include "UrlParseProtocolPuncState.h"
#include "UrlParser.h"

unique_ptr<Token> UrlParseStartState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::str)
	{
		memory.push_back(std::move(token));
	}
	else if (token->type == StdTokenType::punctuation)
	{
		PunctuationToken* pToken = (PunctuationToken*)token.get();
		if (pToken->value == ":")
		{
			// Starting to see format http://xyz
			if (memory.size() == 1)
			{
				auto lastToken = memory[0].get();
				if (lastToken->type == StdTokenType::str)
				{
					// The last token in memory was a string so this is good!
					((UrlParser*)machine)->url.protocol = ((StringToken*)lastToken)->value;
					((UrlParser*)machine)->url.is_fully_qualified = true;
					// Transition to protocol parsing state and return the
					// token to be re-scanned
					auto nextState = new UrlParseProtocolPuncState();
				}
				else
				{
					// The last token in memory wasn't a string
					((UrlParser*)machine)->url.is_valid = false;
				}
			}
			else
			{
				((UrlParser*)machine)->url.is_valid = false;
			}
		}
		else if (pToken->value == "/")
		{
			// Starting to see relative or absolute-relative path
			((UrlParser*)machine)->url.path = "/";
			((UrlParser*)machine)->url.is_relative = true;

			return token;
		}
	}
	if (token->type == StdTokenType::end)
	{

	}
	return nullptr;
}
#include <PunctuationToken.h>

#include "UrlParseProtocolPuncState.h"
#include "UrlParseAuthorityState.h"
#include "UrlParser.h"

unique_ptr<Token> UrlParseProtocolPuncState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::punctuation)
	{
		auto puncToken = (PunctuationToken*)token.get();
		if (puncToken->value == "/")
		{
			if (memory.empty())
			{
				((UrlParser*)machine)->url.is_valid = false;
			}
			if (memory.size() == 1)
			{
				auto colonTok = (Token*)memory[0].get();
				if (colonTok->type == StdTokenType::punctuation)
				{
					auto colonPTok = (PunctuationToken*)colonTok;
					if (colonPTok->value != ":")
					{
						((UrlParser*)machine)->url.is_valid = false;
					}
				}
			}
			if (memory.size() == 2)
			{
				auto colonTok = (Token*)memory[0].get();
				auto firstSlashTok = (Token*)memory[1].get();
				if (colonTok->type == StdTokenType::punctuation)
				{
					auto colonPTok = (PunctuationToken*)colonTok;
					if (colonPTok->value != ":")
					{
						((UrlParser*)machine)->url.is_valid = false;
					}
				}
				if (firstSlashTok->type == StdTokenType::punctuation)
				{
					auto firstSlashPTok = (PunctuationToken*)firstSlashTok;
					if (firstSlashPTok->value != "/")
					{
						((UrlParser*)machine)->url.is_valid = false;
					}
				}
			}
			else
			{
				((UrlParser*)machine)->url.is_valid = false;
			}
		}
		else if (puncToken->value == ":")
		{
			if (memory.empty())
			{
				auto tok = new PunctuationToken(puncToken->value);
				memory.push_back(unique_ptr<Token>(tok));
			}
			else
			{
				((UrlParser*)machine)->url.is_valid = false;
			}
		}
		else
		{
			if (memory.size() == 3)
			{
				auto nextState = new UrlParseAuthorityState();
				transition(shared_ptr<State>(nextState));
			}
			else
			{
				((UrlParser*)machine)->url.is_valid = false;
			}
		}
	}
	else
	{
		auto nextState = new UrlParseAuthorityState();
		transition(unique_ptr<State>(nextState));
		// Transition to next state and do not consume the token
		return token;
	}
	return nullptr;
}
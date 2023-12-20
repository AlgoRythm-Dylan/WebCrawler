#include <PunctuationToken.h>

#include "UrlParser.h"
#include "UrlParseAuthorityState.h"
#include "UrlParsePathState.h"
#include "UrlParseQueryState.h"
#include "UrlParseFragmentState.h"

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
			auto nextState = new UrlParsePathState();
			transition(shared_ptr<State>(nextState));
			// Don't consume token so that the path
			// parsing state may consume it instead
			return token;
		}
		else if (puncToken->value == "?")
		{
			finish();
			transition(new UrlParseQueryState());
		}
		else if (puncToken->value == "#")
		{
			finish();
			transition(new UrlParseFragmentState());
		}
		else
		{
			memory.push_back(std::move(token));
		}
	}
	else if (token->type == StdTokenType::end)
	{
		finish();
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
	auto parser = (UrlParser*)machine;
	// Is there an "@" symbol? - there is a username/password.
	bool foundAtSymbol = false;
	for (auto& token : memory)
	{
		if (token->type == StdTokenType::punctuation)
		{
			auto pToken = (PunctuationToken*)token.get();
			if (pToken->value == "@")
			{
				foundAtSymbol = true;
				break;
			}
		}
	}
	int memoryCursor = 0;
	// Parse as if we are reading username:password@host
	if (foundAtSymbol)
	{
		string username, password;
		// Read up until ":" symbol for username
		while (memoryCursor < memory.size())
		{
			if (memory[memoryCursor]->type == StdTokenType::str)
			{
				username += ((StringToken*)memory[memoryCursor].get())->value;
			}
			else if (memory[memoryCursor]->type == StdTokenType::punctuation)
			{
				auto pToken = (PunctuationToken*)memory[memoryCursor].get();
				if (pToken->value == ":")
				{
					// Colon found, so we have read the whole username
					memoryCursor++;
					break;
				}
				else
				{
					username += pToken->value;
				}
			}
			memoryCursor++;
		}
		// Read up until "@" symbol for password
		while (memoryCursor < memory.size())
		{
			if (memory[memoryCursor]->type == StdTokenType::str)
			{
				password += ((StringToken*)memory[memoryCursor].get())->value;
			}
			else if (memory[memoryCursor]->type == StdTokenType::punctuation)
			{
				auto pToken = (PunctuationToken*)memory[memoryCursor].get();
				if (pToken->value == "@")
				{
					// @ found, so we have read the whole password
					memoryCursor++;
					break;
				}
				else
				{
					password += pToken->value;
				}
			}
			memoryCursor++;
		}
		parser->url.username = username;
		parser->url.password = password;
	}
	// At this point we assume username and password
	// are either already read, or did not exist.
	// ipv6 not supported YET so dots represent separation
	// between parts of a host, anything else is hostname
	string completeHost, currentHostPart;
	while (memoryCursor < memory.size())
	{
		if (memory[memoryCursor]->type == StdTokenType::str)
		{
			currentHostPart += ((StringToken*)memory[memoryCursor].get())->value;
		}
		else if (memory[memoryCursor]->type == StdTokenType::punctuation)
		{
			auto pToken = (PunctuationToken*)memory[memoryCursor].get();
			if (pToken->value == ".")
			{
				completeHost += currentHostPart + ".";
				parser->url.host_parts.push_back(currentHostPart);
				currentHostPart = "";
			}
			else
			{
				currentHostPart += pToken->value;
			}
		}
		memoryCursor++;
	}
	if (currentHostPart.length() > 0)
	{
		// Clean up any remaining host parts
		completeHost += currentHostPart;
		parser->url.host_parts.push_back(currentHostPart);
	}
	parser->url.host = completeHost;
}
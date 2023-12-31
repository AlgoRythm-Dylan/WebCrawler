#include "UrlParseAuthorityState.h"

#include <PunctuationToken.h>
#include <LexingTools.h>

#include "UrlParser.h"
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
	string completeHost, currentHostPart;
	bool parsingipv6 = false;
	int domainCursorStartPosition = memoryCursor;
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
			else if (pToken->value == ":")
			{
				// This *could* be port if:
				// this is the second-to-last token in the buffer
				// the next token is numeric
				if (memoryCursor + 2 == memory.size() &&
					memory[memoryCursor+1]->type == StdTokenType::str)
				{
					auto maybePort = ((StringToken*)memory[memoryCursor+1].get());
					if (LexingTools::is_numeric(maybePort->value))
					{
						parser->url.port = std::stoi(maybePort->value);
						memoryCursor += 2;
						continue;
					}
				}
				else if (parsingipv6 == true)
				{
					completeHost += currentHostPart + ":";
					if (!currentHostPart.empty())
					{
						parser->url.host_parts.push_back(currentHostPart);
						currentHostPart = "";
					}
				}
			}
			else if (pToken->value == "[" && memoryCursor == domainCursorStartPosition)
			{
				completeHost += "[";
				parser->url.is_ipv6 = true;
				parsingipv6 = true;
			}
			else if (parsingipv6 && pToken->value == "]")
			{
				completeHost += currentHostPart + "]";
				if (!currentHostPart.empty())
				{
					parser->url.host_parts.push_back(currentHostPart);
					currentHostPart = "";
				}
				parsingipv6 = false;
			}
			else
			{
				currentHostPart += pToken->value;
			}
		}
		memoryCursor++;
	}
	// If we never encountered a closing square bracket,
	// then the flag for "parsing ipv6" will still be set.
	// This means it's malformed and the URL is invalid
	if (parsingipv6)
	{
		parser->url.is_valid = false;
	}
	if (currentHostPart.length() > 0)
	{
		// Clean up any remaining host parts
		completeHost += currentHostPart;
		parser->url.host_parts.push_back(currentHostPart);
	}
	parser->url.host = completeHost;
	// Check if ipv4
	bool isipv4 = true;
	if (parser->url.host_parts.size() == 4)
	{
		for (const auto& part : parser->url.host_parts)
		{
			if (LexingTools::is_numeric(part))
			{
				int value = std::stoi(part);
				if (value <= 0 || value > 255)
				{
					isipv4 = false;
					break;
				}
			}
			else
			{
				isipv4 = false;
				break;
			}
		}
	}
	else
	{
		isipv4 = false;
	}
	parser->url.is_ipv4 = isipv4;
}
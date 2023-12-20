#include <PunctuationToken.h>
#include <StringToken.h>

#include "UrlParseStartState.h"
#include "UrlParseProtocolPuncState.h"
#include "UrlParsePathState.h"
#include "UrlParseFragmentState.h"
#include "UrlParseQueryState.h"
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
					// Transition to protocol parsing state and return the
					// token to be re-scanned
					auto nextState = std::make_shared<UrlParseProtocolPuncState>();//new UrlParseProtocolPuncState();
					transition(nextState);
					return token;
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
			auto parser = ((UrlParser*)machine);
			// If we have anything in memory, treat it as a relative URL
			if (!memory.empty())
			{
				parser->url.path += serialize_memory();
			}
			// Starting to see relative or absolute-relative path
			parser->url.path = "/";
			parser->url.is_relative = true;
			transition(new UrlParsePathState());
			return token;
		}
		else if (pToken->value == "#")
		{
			auto parser = ((UrlParser*)machine);
			if (!memory.empty())
			{
				parser->url.path += serialize_memory();
			}
			parser->url.is_relative = true;
			transition(new UrlParseFragmentState());
		}
		else if (pToken->value == "?" || pToken->value == "&")
		{
			auto parser = ((UrlParser*)machine);
			if (!memory.empty())
			{
				parser->url.path += serialize_memory();
			}
			parser->url.is_relative = true;
			parser->url.query += pToken->value;
			transition(new UrlParseQueryState());
		}
	}
	else if (token->type == StdTokenType::end)
	{
		
	}
	return nullptr;
}

// BUGBUG: this is not good enough! it only adds to the string, not
// parsing out the path_parts!
string UrlParseStartState::serialize_memory()
{
	string serialized;
	for (auto& tok : memory)
	{
		if (tok->type == StdTokenType::str || tok->type == StdTokenType::punctuation)
		{
			serialized += ((StringToken*)tok.get())->value;
		}
	}
	return serialized;
}
#include "UrlParsePathState.h"

#include <PunctuationToken.h>

#include "UrlParser.h"
#include "UrlParseQueryState.h"
#include "UrlParseFragmentState.h"

unique_ptr<Token> UrlParsePathState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::punctuation)
	{
		auto pToken = (PunctuationToken*)token.get();
		if (pToken->value == "?" || pToken->value == "&")
		{
			// Eject any memory
			if (!memory.empty())
			{
				auto parser = ((UrlParser*)machine);
				parser->url.path_parts.push_back(memory);
				parser->url.path = complete_path + memory;
			}
			// Transition to query parsing state
			auto nextState = new UrlParseQueryState();
			transition(shared_ptr<State>(nextState));
			return token;
		}
		else if (pToken->value == "/")
		{
			auto parser = ((UrlParser*)machine);
			if (!memory.empty())
			{
				parser->url.path_parts.push_back(memory);
			}
			complete_path += memory + "/";
			memory = "";
		}
		else if (pToken->value == "#")
		{
			auto parser = ((UrlParser*)machine);
			if (!memory.empty())
			{
				parser->url.path_parts.push_back(memory);
			}
			complete_path += memory;
			transition(new UrlParseFragmentState());
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
	else if (token->type == StdTokenType::end)
	{
		// Eject any memory
		if (!memory.empty())
		{
			auto parser = ((UrlParser*)machine);
			parser->url.path_parts.push_back(memory);
			parser->url.path = complete_path + memory;
		}
		else if(!complete_path.empty())
		{
			auto parser = ((UrlParser*)machine);
			parser->url.path = complete_path;
		}
	}
	return nullptr;
}
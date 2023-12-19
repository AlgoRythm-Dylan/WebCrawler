#include "UrlParseQueryState.h"

#include <PunctuationToken.h>

#include "UrlParser.h"

unique_ptr<Token> UrlParseQueryState::scan(unique_ptr<Token> token)
{
	// The lexer is smart in this context and
	// does a lot of the work for us. Only punctuation
	// tokens are &, ?, and =

	// Only edge case to cover is multiple consecutive equal signs
	// ?a=b&c=d=d=d=d=d=d=d=d
	// Expected output:
	// a:b
	// c:d=d=d=d=d=d=d=d
	//
	// If key and value are both present and an = is encountered,
	// just add it to the value!
	if (token->type == StdTokenType::str)
	{
		auto sToken = (StringToken*)token.get();
		if (key.empty())
		{
			key = sToken->value;
		}
		else if (value.empty())
		{
			value = sToken->value;
		}
		else if (last_punctuation_seen == "=")
		{
			value += sToken->value;
		}
		else
		{
			// ???????? how. Possible ?? ? ?
			((UrlParser*)machine)->url.is_valid = false;
		}
		complete_query += sToken->value;
	}
	else if (token->type == StdTokenType::punctuation)
	{
		auto pToken = (PunctuationToken*)token.get();
		last_punctuation_seen = pToken->value;
		if (pToken->value == "=" && !value.empty())
		{
			value += "=";
		}
		if (pToken->value == "?" || pToken->value == "&")
		{
			emit_memory();
		}
		complete_query += pToken->value;
	}
	else if (token->type == StdTokenType::end)
	{
		emit_memory();
		((UrlParser*)machine)->url.query = complete_query;
	}
	return nullptr;
}

void UrlParseQueryState::emit_memory()
{
	if (!key.empty())
	{
		((UrlParser*)machine)->url.query_parts.push_back(UrlQueryEntry(key, value));
		key = "";
		value = "";
	}
}
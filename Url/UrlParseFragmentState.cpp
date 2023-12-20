#include "UrlParseFragmentState.h"

#include <StringToken.h>

#include "UrlParser.h"

unique_ptr<Token> UrlParseFragmentState::scan(unique_ptr<Token> token)
{
	auto parser = (UrlParser*)machine;
	if (token->type == StdTokenType::str)
	{
		parser->url.fragment += ((StringToken*)token.get())->value;
	}
	return nullptr;
}
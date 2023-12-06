#include "UrlParseStartState.h"
#include "UrlParser.h"

unique_ptr<Token> UrlParseStartState::scan(unique_ptr<Token> token)
{
	((UrlParser*)machine)->url.protocol = "THIS WORKS!";
	return nullptr;
}
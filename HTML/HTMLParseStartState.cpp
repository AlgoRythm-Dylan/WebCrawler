#include "HTMLParseStartState.h"

#include "HTMLParser.h"

unique_ptr<Token> HTMLParseStartState::scan(unique_ptr<Token> token)
{
	((HTMLParser*)machine)->document.doctype = "THIS WORKS!";
	return nullptr;
}
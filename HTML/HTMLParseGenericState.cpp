#include "HTMLParseGenericState.h"

#include "HTMLParser.h"

unique_ptr<Token> HTMLParseGenericState::scan(unique_ptr<Token> token)
{
	((HTMLParser*)machine)->document.doctype = "THIS WORKS!";
	return nullptr;
}
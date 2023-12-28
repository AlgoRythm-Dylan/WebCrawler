#include "HTMLDocument.h"

#include "HTMLLexer.h"

void HTMLDocument::parse(istream& stream)
{
	HTMLLexer lexer(stream);
}
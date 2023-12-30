#include "HTMLDocument.h"

#include "HTMLLexer.h"
#include "HTMLParser.h"

HTMLDocument::HTMLDocument()
{
	type = HTMLNodeType::Document;
}

void HTMLDocument::parse(istream& stream)
{
	HTMLLexer lexer(stream);
	HTMLParser parser(*this);

	bool running = true;
	while (running)
	{
		auto tok = lexer.next();
		running = tok->type != StdTokenType::end;

		while (tok)
		{
			tok = parser.scan(std::move(tok));
		}
	}
}
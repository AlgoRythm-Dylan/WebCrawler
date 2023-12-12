#include <memory>

#include "URL.h"
#include "UrlLexer.h"
#include "UrlParser.h"

using std::unique_ptr;

Url::Url()
{
	port = 0;
}

Url::Url(string& source)
{
	port = 0;
	parse(source);
}

void Url::parse(string& source)
{
	UrlLexer lexer(source);
	UrlParser parser(*this);

	unique_ptr<Token> tok;
	bool running = true;
	while (running)
	{
		tok = lexer.next();
		running = tok->type != StdTokenType::end;
		// Scanning a token transfers ownership to the parser's
		// current state, but the state may pass the token
		// back if it was not scanned. In this case, the token
		// should be passed back to the parser until it consumes it.
		while (tok)
		{
			tok = parser.scan(std::move(tok));
		}
	}
}
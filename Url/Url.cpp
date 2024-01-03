#include <memory>

#include "URL.h"
#include "UrlLexer.h"
#include "UrlParser.h"

using std::unique_ptr;

Url::Url()
{
	setup_defaults();
}

Url::Url(const string& source)
{
	setup_defaults();
	parse(source);
}

void Url::setup_defaults()
{
	port = 0;
	is_valid = true;
	is_relative = false;
	is_ipv4 = false;
	is_ipv6 = false;
}

void Url::parse(const string& source)
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
		while (tok && is_valid)
		{
			tok = parser.scan(std::move(tok));
			// Exit out of this loop if end token type detected
			if (tok && tok->type == StdTokenType::end)
			{
				break;
			}
		}
	}
}
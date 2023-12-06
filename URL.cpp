#include <memory>

#include "URL.h"
#include "Url/Lexer/UrlLexer.h"

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

	unique_ptr<Token> tok;
	bool running = true;
	while (running)
	{
		tok = lexer.next();
		if (tok->type == StdTokenType::end)
		{
			running = false;
		}
	}
}
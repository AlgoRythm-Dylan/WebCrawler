#include "TokenBufferedLexer.h"

#include <string>
#include <string_view>

#include "PunctuationToken.h"
#include "EOFToken.h"

using std::string;
using std::string_view;

void TokenBufferedLexer::punct(string_view content)
{
	add_token<PunctuationToken>(string(content));
}

void TokenBufferedLexer::str(string_view content)
{
	add_token<StringToken>(string(content));
}

void TokenBufferedLexer::eof()
{
	add_token<EOFToken>();
}
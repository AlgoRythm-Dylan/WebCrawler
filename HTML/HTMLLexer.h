#pragma once

#include <istream>
#include <queue>

#include <Lexer.h>

using std::istream;
using std::queue;

class HTMLLexer : public Lexer
{
protected:
	istream& stream;
public:
	queue<unique_ptr<Token>> token_buffer;

	HTMLLexer(istream&);
	unique_ptr<Token> next();
};

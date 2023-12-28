#pragma once

#include <istream>

#include <Lexer.h>

using std::istream;

class HTMLLexer : public Lexer
{
protected:
	istream& stream;
public:
	HTMLLexer(istream&);
	unique_ptr<Token> next();
};

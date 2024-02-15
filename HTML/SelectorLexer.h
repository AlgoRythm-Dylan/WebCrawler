#pragma once

#include <queue>

#include <Lexer.h>

using std::queue;

class SelectorLexer : public Lexer
{
protected:
	string& source;
	int cursor;
public:
	queue<unique_ptr<Token>> token_buffer;

	SelectorLexer();

	SelectorLexer(string&);
	unique_ptr<Token> next() override;
};

#pragma once

#include <queue>
#include <Lexer.h>

using std::queue;

class UrlLexer : public Lexer
{
protected:
	const string& source;
	int source_caret;
public:
	UrlLexer(const string&);
	unique_ptr<Token> next() override;
	queue<unique_ptr<Token>> token_buffer;
};


#pragma once

#include <queue>
#include "../../Lexer.h"

using std::queue;

class UrlLexer : public Lexer
{
protected:
	string& source;
	int source_caret;
public:
	UrlLexer(string&);
	unique_ptr<Token> next() override;
	queue<unique_ptr<Token>> token_buffer;
};


#pragma once

#include <istream>
#include <queue>

#include <Lexer.h>
#include <StreamHolder.h>

using std::istream;
using std::queue;

class HTMLLexer : public Lexer
{
protected:
	StreamHolder* stream_holder;
public:
	queue<unique_ptr<Token>> token_buffer;

	HTMLLexer();
	HTMLLexer(istream&);
	~HTMLLexer();
	unique_ptr<Token> next() override;
	bool read(const char);
};

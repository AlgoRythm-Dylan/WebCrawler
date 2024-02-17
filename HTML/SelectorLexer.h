#pragma once

#include <queue>

#include <TokenBufferedLexer.h>

using std::queue;

class SelectorLexer : public TokenBufferedLexer
{
protected:
	string& source;
	int cursor;
public:
	SelectorLexer(string&);
	unique_ptr<Token> next() override;
};

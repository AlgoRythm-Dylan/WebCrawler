#pragma once

#include <deque>
#include <ParsingState.h>

using std::deque;

class UrlParseStartState : public ParsingState
{
protected:
	deque<unique_ptr<Token>> memory;
	string serialize_memory();
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};

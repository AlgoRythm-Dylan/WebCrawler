#pragma once

#include <deque>
#include <ParsingState.h>

using std::deque;

class UrlParseStartState : public ParsingState
{
protected:
	deque<unique_ptr<Token>> memory;
	void parse_memory_as_path();
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};

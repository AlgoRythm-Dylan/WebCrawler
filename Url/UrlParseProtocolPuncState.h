#pragma once

#include <deque>

#include <ParsingState.h>

using std::deque;

class UrlParseProtocolPuncState : public ParsingState
{
protected:
	deque<unique_ptr<Token>> memory;
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


#pragma once

#include <deque>

#include <ParsingState.h>
#include <Token.h>

using std::deque;

class UrlParseAuthorityState : public ParsingState
{
protected:
	deque<unique_ptr<Token>> memory;
public:
	unique_ptr<Token> scan(unique_ptr<Token>);
};


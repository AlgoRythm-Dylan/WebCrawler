#pragma once

#include <memory>
#include "StateMachine.h"
#include "Token.h"

using std::unique_ptr;

class Lexer : public StateMachine
{
public:
	int line, col, ch;
	virtual unique_ptr<Token> next() = 0;

	Lexer();

	virtual void update_position(const char);
};

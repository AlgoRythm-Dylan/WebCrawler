#pragma once

#include <memory>
#include "StateMachine.h"
#include "Token.h"

using std::unique_ptr;

class Lexer : public StateMachine
{
public:
	virtual unique_ptr<Token> next() = 0;
};

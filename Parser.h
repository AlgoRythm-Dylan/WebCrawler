#pragma once

#include <memory>
#include "StateMachine.h"
#include "Token.h"

using std::unique_ptr;

class Parser : public StateMachine
{
public:
	virtual unique_ptr<Token> scan(unique_ptr<Token>) = 0;
};


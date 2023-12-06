#pragma once

#include <memory>
#include "State.h"
#include "Token.h"

using std::unique_ptr;

class ParsingState : public State
{
public:
	virtual unique_ptr<Token> scan(unique_ptr<Token>) = 0;
};
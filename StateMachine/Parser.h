#pragma once

#include <memory>
#include <vector>

#include "StateMachine.h"
#include "Token.h"
#include "ParserMessage.h"

using std::vector;
using std::unique_ptr;

class Parser : public StateMachine
{
public:
	vector<ParserMessage> messages;

	virtual unique_ptr<Token> scan(unique_ptr<Token>) = 0;
};


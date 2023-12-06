#pragma once

#include "State.h"
#include "LexingScanResult.h"

class LexingState : public State
{
public:
	virtual LexingScanResult scan(const char) = 0;
};


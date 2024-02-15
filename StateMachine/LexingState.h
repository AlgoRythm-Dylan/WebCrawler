#pragma once

#include "State.h"

class LexingState : public State
{
public:
	/* Returns true if token consumed */
	virtual bool scan(const char) = 0;
};


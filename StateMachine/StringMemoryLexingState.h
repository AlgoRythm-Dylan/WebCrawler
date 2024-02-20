#pragma once

#include <string>

#include "LexingState.h"

using std::string;

class StringMemoryLexingState : public LexingState
{
protected:
	string memory;
	virtual void emit_memory();
};

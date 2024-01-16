#pragma once

#include <string>

#include <LexingState.h>

using std::string;

class HTMLStringMemoryState : public LexingState
{
protected:
	string memory;

	virtual void emit_memory();
};


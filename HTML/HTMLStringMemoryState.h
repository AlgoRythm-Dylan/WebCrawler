#pragma once

#include <string>

#include <LexingState.h>

using std::string;

class HTMLStringMemoryState : public LexingState
{
protected:
	string memory;

	void emit_memory();
};


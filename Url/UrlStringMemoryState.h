#pragma once

#include <string>
#include <LexingState.h>

using std::string;

class UrlStringMemoryState : public LexingState
{
protected:
	string memory;

	void emit_memory();
};

#pragma once
#include "HTMLStringMemoryState.h"
class HTMLLexWhitespaceState : public HTMLStringMemoryState
{
public:
	shared_ptr<State> return_state;

	LexingScanResult scan(const char) override;
};


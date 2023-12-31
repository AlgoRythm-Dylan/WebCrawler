#pragma once
#include "HTMLStringMemoryState.h"

class HTMLLexTagState : public HTMLStringMemoryState
{
protected:
	int counter;
	string token_memory;
public:
	HTMLLexTagState();

	LexingScanResult scan(const char) override;
};


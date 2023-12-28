#pragma once

#include "HTMLStringMemoryState.h"

class HTMLLexGenericState : public HTMLStringMemoryState
{
public:
	LexingScanResult scan(const char) override;
};


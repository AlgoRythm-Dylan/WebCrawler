#pragma once
#include "HTMLStringMemoryState.h"

class HTMLLexTagState : public HTMLStringMemoryState
{
public:
	LexingScanResult scan(const char) override;
};


#pragma once

#include "HTMLStringMemoryState.h"

class HTMLLexGenericState : public HTMLStringMemoryState
{
public:
	bool scan(const char) override;
};


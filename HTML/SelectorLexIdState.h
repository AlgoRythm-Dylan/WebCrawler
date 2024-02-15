#pragma once

#include "SelectorStringMemoryState.h"

class SelectorLexIdState : public SelectorStringMemoryState
{
public:
	bool scan(const char) override;
};

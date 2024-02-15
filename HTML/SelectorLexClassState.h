#pragma once

#include "SelectorStringMemoryState.h"

class SelectorLexClassState : public SelectorStringMemoryState
{
public:
	bool scan(const char) override;
};

#pragma once

#include <LexingState.h>

class SelectorLexGenericState : public LexingState
{
public:
	bool scan(const char) override;
};


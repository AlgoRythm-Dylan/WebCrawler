#pragma once

#include <StringMemoryLexingState.h>

class SelectorLexGenericState : public StringMemoryLexingState
{
public:
	bool scan(const char) override;
};


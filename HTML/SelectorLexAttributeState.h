#pragma once

#include <StringMemoryLexingState.h>

class SelectorLexAttributeState : public StringMemoryLexingState
{
public:
	bool scan(const char) override;
};

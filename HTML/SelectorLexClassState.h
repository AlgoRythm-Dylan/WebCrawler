#pragma once

#include <StringMemoryLexingState.h>

class SelectorLexClassState : public StringMemoryLexingState
{
public:
	bool scan(const char) override;
};

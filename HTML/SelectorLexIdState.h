#pragma once

#include <StringMemoryLexingState.h>

class SelectorLexIdState : public StringMemoryLexingState
{
public:
	bool scan(const char) override;
};

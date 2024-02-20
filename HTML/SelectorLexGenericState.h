#pragma once

#include <StringMemoryLexingState.h>

class SelectorLexGenericState : public StringMemoryLexingState
{
public:
	bool last_char_was_whitespace = false;

	SelectorLexGenericState();

	bool scan(const char) override;
};


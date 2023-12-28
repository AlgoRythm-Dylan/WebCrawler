#pragma once

#include <LexingState.h>

class HTMLLexStartState : public LexingState
{
public:
	LexingScanResult scan(const char) override;
};


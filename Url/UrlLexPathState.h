#pragma once
#include <LexingState.h>

class UrlLexPathState : public LexingState
{
protected:
	string memory;
	void emit_memory();
public:
	LexingScanResult scan(const char) override;
};


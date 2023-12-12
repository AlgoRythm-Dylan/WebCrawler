#pragma once

#include <LexingState.h>
#include <LexingScanResult.h>

class UrlLexStartState : public LexingState
{
protected:
	string memory;
	void emit_memory();
public:
	LexingScanResult scan(const char) override;
};


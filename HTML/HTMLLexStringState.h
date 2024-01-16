#pragma once

#include "HTMLStringMemoryState.h"

class HTMLLexStringState : public HTMLStringMemoryState
{
public:
	// This state will likely return to a previous
	// state instead of transitioning to a new one
	shared_ptr<State> return_state;
	char opening_quote;
	bool escape_flag;

	HTMLLexStringState();
	HTMLLexStringState(const char open);
	LexingScanResult scan(const char) override;

	// An empty string is still a string
	void emit_memory() override;
};


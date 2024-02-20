#pragma once

#include <StringMemoryLexingState.h>

class SelectorLexStringState : public StringMemoryLexingState
{
public:
	// This state will likely return to a previous
	// state instead of transitioning to a new one
	shared_ptr<State> return_state;
	char opening_quote;
	bool escape_flag;

	SelectorLexStringState();
	SelectorLexStringState(const char open);

	bool scan(const char) override;


	// Need to override default behavior and emit
	// empty string tokens
	void emit_memory() override;
};

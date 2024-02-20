#include "SelectorLexAttributeState.h"

#include "SelectorLexer.h"
#include "SelectorLexStringState.h"

bool SelectorLexAttributeState::scan(const char character)
{
	if (character == ']')
	{
		emit_memory();
		auto lexer = (SelectorLexer*)machine;
		lexer->punct("]");
	}
	else if (character == '=')
	{
		emit_memory();
		auto lexer = (SelectorLexer*)machine;
		lexer->punct("=");

	}
	else if (character == '\"' || character == '\'')
	{
		emit_memory();
		auto nextState = new SelectorLexStringState();
		nextState->return_state = machine->current_state; // this
		transition(nextState);
	}
	else if (character == '\0')
	{
		emit_memory();
		auto lexer = (SelectorLexer*)machine;
		lexer->eof();
	}
	else
	{
		memory += character;
	}
}
#include "SelectorLexStringState.h"

#include "SelectorLexer.h"
#include "SelectorLexGenericState.h"

SelectorLexStringState::SelectorLexStringState()
{
	opening_quote = '\"';
	escape_flag = false;
}

SelectorLexStringState::SelectorLexStringState(const char open)
{
	opening_quote = open;
	escape_flag = false;
}

bool SelectorLexStringState::scan(const char character)
{
	if (character == '\\')
	{
		if (escape_flag)
		{
			memory += character;
		}
		else
		{
			escape_flag = true;
		}
	}
	else if (character == opening_quote && !escape_flag)
	{
		emit_memory();
		if (return_state)
		{
			machine->current_state = return_state;
		}
		else
		{
			transition(new SelectorLexGenericState());
		}
	}
	else
	{
		memory += character;
	}
	if (escape_flag)
	{
		escape_flag = false;
	}
}

void SelectorLexStringState::emit_memory()
{
	auto lexer = (SelectorLexer*)machine;
	lexer->str(memory);
	memory = "";
}
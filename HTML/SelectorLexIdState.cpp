#include "SelectorLexIdState.h"

#include <memory>

#include <EOFToken.h>
#include <PunctuationToken.h>

#include "SelectorLexer.h"
#include "SelectorLexClassState.h"

using std::unique_ptr;

bool SelectorLexIdState::scan(const char character)
{
	// If find [, transition to attribute parsing state
	// If find ., transition to class parsing state
	// if find whitespace, transition to generic state
	// else, add to memory (it's the tag name!)
	if (character == '[')
	{
		emit_memory();
	}
	else if (character == '.')
	{
		emit_memory();
		auto lexer = (SelectorLexer*)machine;
		lexer->add_token<PunctuationToken>(".");
		transition(new SelectorLexClassState());
	}
	else if (character == ' ')
	{
		emit_memory();
	}
	else if (character == '\0')
	{
		emit_memory();
		auto lexer = (SelectorLexer*)machine;
		lexer->add_token<EOFToken>();
	}
	else
	{
		memory += character;
	}
	return true;
}
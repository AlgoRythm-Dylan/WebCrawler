#include "HTMLLexGenericState.h"

#include "HTMLLexer.h"

#include <EOFToken.h>

/*

This state is responsible for generic HTML lexing. Once
an opening tag symbol is encountered, a transition
begins to the tag lexing state. Everything else is treated
as text

Tokens include:

<             Start tag punctuation

*/


LexingScanResult HTMLLexGenericState::scan(const char character)
{
	LexingScanResult result;
	if (character == '<')
	{
		emit_memory();
	}
	else if (character == '\0')
	{
		emit_memory();

		((HTMLLexer*)machine)->token_buffer.push(unique_ptr<Token>(new EOFToken()));
	}
	else
	{
		memory += character;
	}
	return result;
}
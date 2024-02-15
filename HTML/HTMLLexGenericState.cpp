#include "HTMLLexGenericState.h"

#include <EOFToken.h>
#include <PunctuationToken.h>

#include "HTMLLexer.h"
#include "HTMLLexTagState.h"

/*

This state is responsible for generic HTML lexing. Once
an opening tag symbol is encountered, a transition
begins to the tag lexing state. Everything else is treated
as text

Tokens include:

<             Start tag punctuation

*/


bool HTMLLexGenericState::scan(const char character)
{
	if (character == '<')
	{
		emit_memory();

		auto tok = new PunctuationToken("<");
		((HTMLLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));

		transition(new HTMLLexTagState());
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
	return true;
}
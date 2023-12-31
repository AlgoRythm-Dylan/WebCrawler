#include "HTMLLexTagState.h"

#include <PunctuationToken.h>
#include <EOFToken.h>

#include "HTMLLexer.h"
#include "HTMLLexStringState.h"
#include "HTMLLexGenericState.h"

/*

This state is responsible for lexing tags, AKA, everything
between < and >. This includes attributes and the end tag
indicator (/)

Tokens include:

<             Start tag punctuation
>             End tag punctuation
/             Closing tag indicator
=             Attribute assignment operator
"             Attribute string start
'             Attribute string start (alternative)
!             Start of comment OR doctype
-             Comment syntax

*/

LexingScanResult HTMLLexTagState::scan(const char character)
{
	LexingScanResult result;
	if (character == '<' || character == '>' ||
        character == '/' || character == '=' ||
		character == '"' || character == '\'' ||
		character == '!' || character == '-')
	{
		emit_memory();

		auto pToken = new PunctuationToken(string(1, character));
		((HTMLLexer*)machine)->token_buffer.push(unique_ptr<Token>(pToken));

		if (character == '>')
		{
			transition(new HTMLLexGenericState());
		}
		else if (character == '"' || character == '\'')
		{
			auto nextState = new HTMLLexStringState(character);
			// If we construct a new shared pointer and simply pass
			// this, the shared pointer on the machine will free us.
			// We want to use the shared pointer on the machine instead.
			nextState->return_state = this->machine->current_state;
			transition(nextState);
		}
	}
	else if (character == ' ' || character == '\n')
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
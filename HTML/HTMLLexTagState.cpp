#include "HTMLLexTagState.h"

#include <PunctuationToken.h>
#include <EOFToken.h>
#include <LexingTools.h>

#include "HTMLLexer.h"
#include "HTMLLexStringState.h"
#include "HTMLLexGenericState.h"
#include "HTMLLexCommentState.h"
#include "HTMLLexWhitespaceState.h"

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

HTMLLexTagState::HTMLLexTagState()
{
	counter = 0;
}

LexingScanResult HTMLLexTagState::scan(const char character)
{
	LexingScanResult result;
	if (character == '<' || character == '>' ||
        character == '/' || character == '=' ||
		character == '"' || character == '\'' ||
		character == '!' || character == '-')
	{
		emit_memory();

		if (character != '"' && character != '\'')
		{
			auto pToken = new PunctuationToken(string(1, character));
			((HTMLLexer*)machine)->token_buffer.push(unique_ptr<Token>(pToken));
		}

		if (counter <= 2)
		{
			token_memory += character;
		}

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
		// On the third iteration, counter will be 2
		// ! - -
		// 0 1 2
		else if (counter == 2 && character == '-' && token_memory == "!--")
		{
			// This is a comment
			transition(new HTMLLexCommentState());
		}
	}
	else if (LexingTools::is_whitespace(character))
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
	counter++;
	return result;
}
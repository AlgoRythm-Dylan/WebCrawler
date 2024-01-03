#include "HTMLLexWhitespaceState.h"

#include <WhitespaceToken.h>
#include <StateMachine.h>

#include <LexingTools.h>

#include "HTMLLexGenericState.h"

LexingScanResult HTMLLexWhitespaceState::scan(const char character)
{
	LexingScanResult result;
	if (LexingTools::is_whitespace(character))
	{
		memory += character;
	}
	else
	{
		if (return_state)
		{
			machine->current_state = return_state;
		}
		else
		{
			transition(new HTMLLexGenericState());
		}
	}
	return result;
}
#include "HTMLLexWhitespaceState.h"

#include <WhitespaceToken.h>
#include <StateMachine.h>

#include <LexingTools.h>

#include "HTMLLexGenericState.h"
#include "HTMLLexer.h"

bool HTMLLexWhitespaceState::scan(const char character)
{
	bool consumed = true;
	if (LexingTools::is_whitespace(character))
	{
		memory += character;
	}
	else
	{
		auto token = new WhitespaceToken();
		token->value = memory;
		auto lexer = (HTMLLexer*)machine;
		lexer->token_buffer.push(unique_ptr<Token>(token));
		consumed = false;
		if (return_state)
		{
			machine->current_state = return_state;
		}
		else
		{
			transition(new HTMLLexGenericState());
		}
	}
	return consumed;
}
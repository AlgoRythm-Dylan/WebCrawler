#include "HTMLLexStringState.h"

#include <PunctuationToken.h>
#include <EOFToken.h>

#include "HTMLLexer.h"
#include "HTMLLexGenericState.h"

HTMLLexStringState::HTMLLexStringState()
{
	opening_quote = '"';
	escape_flag = false;
}

HTMLLexStringState::HTMLLexStringState(const char open)
{
	opening_quote = open;
	escape_flag = false;
}

bool HTMLLexStringState::scan(const char character)
{
	if (character == opening_quote && !escape_flag)
	{
		emit_memory();
		/*auto pToken = new PunctuationToken(string(1, opening_quote));
		((HTMLLexer*)machine)->token_buffer.push(unique_ptr<Token>(pToken));*/
		if (return_state)
		{
			machine->current_state = return_state;
		}
		else
		{
			transition(new HTMLLexGenericState());
		}
	}
	else if (character == '\\' && !escape_flag)
	{
		escape_flag = true;
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

	// Clear the escape flag
	if (character != '\\' && escape_flag)
	{
		escape_flag = false;
	}

	return true;
}

void HTMLLexStringState::emit_memory()
{
	auto lexer_pointer = (HTMLLexer*)machine;
	auto new_token = new StringToken(memory);
	lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
	memory = "";
}
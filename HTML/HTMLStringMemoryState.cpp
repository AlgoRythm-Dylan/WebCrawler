#include "HTMLStringMemoryState.h"

#include "HTMLLexer.h"
#include <StringToken.h>

void HTMLStringMemoryState::emit_memory()
{
	auto lexer_pointer = (HTMLLexer*)machine;
	if (memory.length() != 0)
	{
		auto new_token = new StringToken(memory);
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
	}
	memory = "";
}
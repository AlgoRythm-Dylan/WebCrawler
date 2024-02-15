#include "SelectorStringMemoryState.h"

#include "SelectorLexer.h"
#include <StringToken.h>

void SelectorStringMemoryState::emit_memory()
{
	auto lexer_pointer = (SelectorLexer*)machine;
	if (!memory.empty())
	{
		auto new_token = new StringToken(memory);
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
	}
	memory = "";
}
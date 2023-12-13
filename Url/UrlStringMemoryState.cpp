#include "UrlStringMemoryState.h"

#include "UrlLexer.h"
#include <StringToken.h>

void UrlStringMemoryState::emit_memory()
{
	auto lexer_pointer = (UrlLexer*)machine;
	if (memory.length() != 0)
	{
		auto new_token = new StringToken(memory);
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
	}
	memory = "";
}
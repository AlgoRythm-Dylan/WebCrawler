#include "UrlLexPathState.h"
#include "UrlLexer.h"
#include <StringToken.h>

LexingScanResult UrlLexPathState::scan(const char character)
{
	LexingScanResult result;
	if (character == '/')
	{
		emit_memory();
		// Create punctuation token
	}
	else if (character == '?')
	{
		// Emit memory and then transition to URL param parse state
	}
	else
	{
		memory += character;
	}
	return result;
}

void UrlLexPathState::emit_memory()
{
	auto lexer_pointer = (UrlLexer*)machine;
	if (memory.length() != 0)
	{
		auto new_token = new StringToken(memory);
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
	}
	memory = "";
}
#include "UrlLexFragmentState.h"

#include "UrlLexer.h"

#include <EOFToken.h>

LexingScanResult UrlLexFragmentState::scan(const char character)
{
	LexingScanResult result;
	if (character == '\0')
	{
		emit_memory();
		auto tok = new EOFToken();
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
	}
	else
	{
		memory += character;
	}
	return result;
}
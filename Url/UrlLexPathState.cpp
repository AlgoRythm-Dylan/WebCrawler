#include "UrlLexPathState.h"
#include "UrlLexer.h"
#include <StringToken.h>
#include <PunctuationToken.h>
#include <EOFToken.h>

LexingScanResult UrlLexPathState::scan(const char character)
{
	LexingScanResult result;
	if (character == '/')
	{
		emit_memory();
		// Create punctuation token
		auto tok = new PunctuationToken("/");
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
	}
	else if (character == '?')
	{
		// Emit memory and then transition to URL param parse state
	}
	else if (character == '\0')
	{
		emit_memory();
		// Create end token
		auto tok = new EOFToken();
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
	}
	else
	{
		memory += character;
	}
	return result;
}

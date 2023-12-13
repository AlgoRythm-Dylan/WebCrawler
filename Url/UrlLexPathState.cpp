#include "UrlLexPathState.h"
#include "UrlLexer.h"
#include <StringToken.h>
#include <PunctuationToken.h>

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
	else
	{
		memory += character;
	}
	return result;
}

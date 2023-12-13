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
#include "UrlLexFragmentState.h"

LexingScanResult UrlLexFragmentState::scan(const char character)
{
	LexingScanResult result;
	if (character == '\0')
	{
		emit_memory();
	}
	else
	{
		memory += character;
	}
	return result;
}
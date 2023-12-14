#include "UrlLexFragmentState.h"

LexingScanResult UrlLexFragmentState::scan(const char character)
{
	if (character == '\0')
	{
		emit_memory();
	}
	else
	{
		memory += character;
	}
}
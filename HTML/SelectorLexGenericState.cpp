#include "SelectorLexGenericState.h"

#include <PunctuationToken.h>

#include "SelectorLexer.h"

bool SelectorLexGenericState::scan(const char character)
{
	// Punctuation for id, class, and rule separator, respectively
	if (character == '#' || character == '.' || character == ',')
	{
		emit_memory();
		auto lexer = (SelectorLexer*)machine;
		lexer->punct(string(character, 1));
	}
	/*else if (character == '[')
	{

	}*/
	else
	{
		if (character == ' ')
		{
			emit_memory();
			auto lexer = (SelectorLexer*)machine;
			lexer->wsp();
		}
		else
		{
			memory += character;
		}
	}
	return true;
}
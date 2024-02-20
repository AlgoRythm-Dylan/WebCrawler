#include "SelectorLexGenericState.h"

#include <PunctuationToken.h>
#include <LexingTools.h>

#include "SelectorLexer.h"

SelectorLexGenericState::SelectorLexGenericState()
{
	last_char_was_whitespace = false;
}

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
		if (LexingTools::is_whitespace(character))
		{
			if (!last_char_was_whitespace)
			{
				emit_memory();
				auto lexer = (SelectorLexer*)machine;
				lexer->wsp();
			}
		}
		else
		{
			memory += character;
		}
	}
	if (LexingTools::is_whitespace(character))
	{
		last_char_was_whitespace = true;
	}
	return true;
}
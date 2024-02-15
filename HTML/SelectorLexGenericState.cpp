#include "SelectorLexGenericState.h"

#include <PunctuationToken.h>

#include "SelectorLexer.h"
#include "SelectorLexIdState.h"
#include "SelectorLexClassState.h"

bool SelectorLexGenericState::scan(const char character)
{
	// If the character is a #, this is an ID
	// if the character is a ., this is a class name
	// if the character is a [, this is an attribtue
	// if whitespace, ignore
	// else, this is a tag name
	if (character == '#')
	{
		auto token = unique_ptr<Token>(new PunctuationToken("#"));
		auto lexer = (SelectorLexer*)machine;
		lexer->token_buffer.push(token);
		transition(new SelectorLexIdState());
	}
	else if (character == '.')
	{
		auto token = unique_ptr<Token>(new PunctuationToken("."));
		auto lexer = (SelectorLexer*)machine;
		lexer->token_buffer.push(token);
		transition(new SelectorLexClassState());
	}
	else if (character == '[')
	{

	}
	else
	{
		if (character != ' ')
		{

		}
	}
	return true;
}
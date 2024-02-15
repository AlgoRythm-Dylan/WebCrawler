#include "SelectorLexClassState.h"

#include <memory>

#include <PunctuationToken.h>
#include <EOFToken.h>

#include "SelectorLexer.h"
#include "SelectorLexIdState.h"

using std::unique_ptr;

bool SelectorLexClassState::scan(const char character)
{
	// If character is ., emit memory then emit punctuation
	// If character is #, transition to ID parsing state
	// if character is [, transition to attribute parsing state
	// if character is whitespace, trasition to generic state
	// else, add to memory!
	if (character == '.')
	{
		emit_memory();
		auto token = unique_ptr<Token>(new PunctuationToken("."));
		auto lexer = (SelectorLexer*)machine;
		lexer->token_buffer.push(std::move(token));
	}
	else if (character == '#')
	{
		emit_memory();
		auto token = unique_ptr<Token>(new PunctuationToken("#"));
		auto lexer = (SelectorLexer*)machine;
		lexer->token_buffer.push(std::move(token));
		transition(new SelectorLexIdState());
	}
	else if (character == '\0')
	{
		emit_memory();
		auto token = unique_ptr<Token>(new EOFToken());
		auto lexer = (SelectorLexer*)machine;
		lexer->token_buffer.push(std::move(token));
	}
	else
	{
		memory += character;
	}
	return true;
}
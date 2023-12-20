#include "UrlLexPathState.h"

#include <StringToken.h>
#include <PunctuationToken.h>
#include <EOFToken.h>

#include "UrlLexer.h"
#include "UrlLexQueryState.h"
#include "UrlLexFragmentState.h"

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
	else if (character == '?' || character == '&')
	{
		emit_memory();
		result.consumed = false;
		auto nextState = new UrlLexQueryState();
		transition(shared_ptr<State>(nextState));
	}
	else if (character == '#')
	{
		emit_memory();
		auto tok = new PunctuationToken("#");
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
		auto nextState = new UrlLexFragmentState();
		transition(shared_ptr<State>(nextState));
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

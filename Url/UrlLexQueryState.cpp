#include <PunctuationToken.h>
#include <EOFToken.h>

#include "UrlLexQueryState.h"
#include "UrlLexFragmentState.h"
#include "UrlLexer.h"

LexingScanResult UrlLexQueryState::scan(const char character)
{
	LexingScanResult result;
	if (character == '?' || character == '=' || character == '&')
	{
		emit_memory();
		auto tok = new PunctuationToken(string(1, character));
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
	}
	else if (character == '\0')
	{
		emit_memory();
		auto tok = new EOFToken();
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
	}
	else if (character == '#')
	{
		emit_memory();
		auto tok = new PunctuationToken("#");
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(tok));
		// Parse fragment
		auto nextState = new UrlLexFragmentState();
		transition(shared_ptr<State>(nextState));
	}
	else
	{
		memory += character;
	}
	return result;
}

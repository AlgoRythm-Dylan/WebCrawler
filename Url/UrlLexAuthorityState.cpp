#include <PunctuationToken.h>
#include <EOFToken.h>

#include "UrlLexAuthorityState.h"
#include "UrlLexPathState.h"
#include "UrlLexer.h"

LexingScanResult UrlLexAuthorityState::scan(const char character)
{
	LexingScanResult result;
	if (character == '/')
	{
		result.consumed = false;
		// Transition to path parsing state
		auto pathParsingState = std::make_shared<UrlLexPathState>();
		transition(pathParsingState);
	}
	else if (character == '.' || character == ':' || character == '@')
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
	else
	{
		memory += character;
	}
	return result;
}
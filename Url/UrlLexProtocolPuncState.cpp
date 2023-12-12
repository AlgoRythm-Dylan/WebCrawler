#include "UrlLexProtocolPuncState.h"

#include <PunctuationToken.h>
#include <EOFToken.h>
#include "UrlLexer.h"

LexingScanResult UrlLexProtocolPuncState::scan(const char character)
{
	LexingScanResult result;
	if (character == ':' || character == '/')
	{
		// Push punctuation token onto queue
		auto token = new PunctuationToken(string(1, character));
		((UrlLexer*)machine)->token_buffer.push(std::unique_ptr<Token>(token));
	}
	else
	{
		// Transition to next state
		// TEMP: just end the parsing
		auto token = new EOFToken();
		((UrlLexer*)machine)->token_buffer.push(std::unique_ptr<Token>(token));
	}
	return result;
}
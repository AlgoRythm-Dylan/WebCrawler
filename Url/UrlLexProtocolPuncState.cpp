#include "UrlLexProtocolPuncState.h"

#include <PunctuationToken.h>
#include <EOFToken.h>
#include "UrlLexer.h"
#include "UrlLexAuthorityState.h"

bool UrlLexProtocolPuncState::scan(const char character)
{
	bool consumed = true;
	if (character == ':' || character == '/')
	{
		// Push punctuation token onto queue
		auto token = new PunctuationToken(string(1, character));
		((UrlLexer*)machine)->token_buffer.push(std::unique_ptr<Token>(token));
	}
	else if (character == '\0')
	{
		((UrlLexer*)machine)->token_buffer.push(unique_ptr<Token>(new EOFToken()));
	}
	else
	{
		// Transition to next state
		consumed = false;
		auto nextState = new UrlLexAuthorityState();
		transition(shared_ptr<State>(nextState));
	}
	return consumed;
}
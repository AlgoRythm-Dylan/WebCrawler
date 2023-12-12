#include "UrlLexProtocolPuncState.h"

LexingScanResult UrlLexProtocolPuncState::scan(const char character)
{
	LexingScanResult result;
	if (character == ':' || character == '/')
	{
		// Push punctuation token onto queue
	}
	else
	{
		// Transition to next state
	}
	return result;
}
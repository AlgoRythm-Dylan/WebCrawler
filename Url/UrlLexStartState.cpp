#include "UrlLexStartState.h"
#include "UrlLexer.h"
#include <StringToken.h>
#include <PunctuationToken.h>
#include "UrlLexProtocolPuncState.h"

using std::unique_ptr;

LexingScanResult UrlLexStartState::scan(const char character)
{
	LexingScanResult result;
	if (character == ' ')
	{
		if (memory.length() != 0)
		{
			memory += ' ';
		}
	}
	else if (character == ':')
	{
		// Transition to protocol punctuation lexing state
		// emit memory as a string token if not empty
		auto lexer_pointer = (UrlLexer*)machine;
		if (memory.length() != 0)
		{
			auto new_token = new StringToken();
			new_token->value = memory;
			lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
		}
		auto new_punc_token = new PunctuationToken();
		new_punc_token->value = ":";
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_punc_token));
		auto next_state = std::make_shared<UrlLexProtocolPuncState>();
		transition(next_state);
	}
	else if (character == '/')
	{
		// Transition to path parsing state
	}
	else if (character == '?')
	{
		// Transition to query parsing state
	}
	return result;
}
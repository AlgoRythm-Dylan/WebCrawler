#include "UrlLexStartState.h"
#include "UrlLexer.h"
#include <StringToken.h>
#include <PunctuationToken.h>
#include "UrlLexProtocolPuncState.h"
#include "UrlLexPathState.h"

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
		emit_memory();
		auto new_punc_token = new PunctuationToken(":");
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_punc_token));
		auto next_state = std::make_shared<UrlLexProtocolPuncState>();
		transition(next_state);
	}
	else if (character == '/')
	{
		// Transition to path parsing state
		emit_memory();
		result.consumed = false;
		auto next_state = std::make_shared<UrlLexPathState>();
		transition(next_state);
	}
	else if (character == '?')
	{
		// Transition to query parsing state
	}
	else
	{
		// Nothing to do here except remember what we're being told
		memory += character;
	}
	return result;
}


// If any memory, emit it as a token to the token buffer
// as a string token
void UrlLexStartState::emit_memory()
{
	auto lexer_pointer = (UrlLexer*)machine;
	if (memory.length() != 0)
	{
		auto new_token = new StringToken(memory);
		lexer_pointer->token_buffer.push(unique_ptr<Token>(new_token));
	}
	memory = "";
}
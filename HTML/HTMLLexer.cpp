#include "HTMLLexer.h"

#include <EOFToken.h>

#include "HTMLLexStartState.h"

HTMLLexer::HTMLLexer(istream& s) : stream(s)
{
	current_state = unique_ptr<State>(new HTMLLexStartState());
	current_state->machine = this;
}

unique_ptr<Token> HTMLLexer::next()
{
	return unique_ptr<Token>(new EOFToken());
}
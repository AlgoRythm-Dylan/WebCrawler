#include "HTMLLexer.h"

#include "HTMLLexStartState.h"

HTMLLexer::HTMLLexer()
{
	current_state = unique_ptr<State>(new HTMLLexStartState());
	current_state->machine = this;
}
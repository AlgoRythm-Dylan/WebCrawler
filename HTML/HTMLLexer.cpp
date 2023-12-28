#include "HTMLLexer.h"

#include <EOFToken.h>

#include "HTMLLexGenericState.h"

HTMLLexer::HTMLLexer(istream& s) : stream(s)
{
	current_state = unique_ptr<State>(new HTMLLexGenericState());
	current_state->machine = this;
}

unique_ptr<Token> HTMLLexer::next()
{
	if (!token_buffer.empty())
	{
		auto token = std::move(token_buffer.front());
		token_buffer.pop();
		return token;
	}

	while (token_buffer.empty())
	{
		auto lexing_state = std::static_pointer_cast<LexingState>(current_state);
		LexingScanResult result;

		char to_scan;
		stream.get(to_scan);

		result = lexing_state->scan(to_scan);
		if (!result.consumed)
		{
			stream.putback(to_scan);
		}
	}

	return unique_ptr<Token>(new EOFToken());
}
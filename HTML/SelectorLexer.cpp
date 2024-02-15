#include "SelectorLexer.h"

#include <LexingState.h>

#include "SelectorLexGenericState.h"

SelectorLexer::SelectorLexer(string& input) : source(input)
{
	current_state = unique_ptr<State>(new SelectorLexGenericState());
	current_state->machine = this;
	cursor = 0;
}

unique_ptr<Token> SelectorLexer::next()
{
	if (!token_buffer.empty())
	{
		auto token = std::move(token_buffer.front());
		token_buffer.pop();
		return token;
	}

	while (token_buffer.empty())
	{
		auto lexingState = std::static_pointer_cast<LexingState>(current_state);
		bool consumed;
		char toScan;

		if (cursor == source.size())
		{
			toScan = '\n';
		}
		else
		{
			toScan = source[cursor];
		}
		bool consumed = lexingState->scan(toScan);
		if (consumed)
		{
			cursor++;
		}
	}
	auto token = std::move(token_buffer.front());
	token_buffer.pop();
	return token;
}
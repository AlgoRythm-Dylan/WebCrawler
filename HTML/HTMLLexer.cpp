#include "HTMLLexer.h"

#include <EOFToken.h>

#include "HTMLLexGenericState.h"

HTMLLexer::HTMLLexer()
{
	stream_holder = nullptr;
	current_state = unique_ptr<State>(new HTMLLexGenericState());
	current_state->machine = this;
}

HTMLLexer::HTMLLexer(istream& s)
{
	stream_holder = new StreamHolder(s);
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
		
		stream_holder->stream.get(to_scan);
		if (stream_holder->stream.eof())
		{
			to_scan = '\0';
		}

		result = lexing_state->scan(to_scan);
		if (!result.consumed)
		{
			stream_holder->stream.putback(to_scan);
		}
	}
	auto token = std::move(token_buffer.front());
	token_buffer.pop();
	return token;
}

LexingScanResult HTMLLexer::read(const char character)
{
	auto lexing_state = std::static_pointer_cast<LexingState>(current_state);

	return lexing_state->scan(character);
}

HTMLLexer::~HTMLLexer()
{
	if (stream_holder)
	{
		delete stream_holder;
	}
}
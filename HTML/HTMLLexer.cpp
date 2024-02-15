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
		auto lexingState = std::static_pointer_cast<LexingState>(current_state);
		bool consumed;

		char toScan;
		
		stream_holder->stream.get(toScan);
		if (stream_holder->stream.eof())
		{
			toScan = '\0';
		}

		consumed = lexingState->scan(toScan);
		if (!consumed)
		{
			stream_holder->stream.putback(toScan);
		}
		else
		{
			update_position(toScan);
		}
	}
	auto token = std::move(token_buffer.front());
	token_buffer.pop();
	return token;
}

bool HTMLLexer::read(const char character)
{
	auto lexingState = std::static_pointer_cast<LexingState>(current_state);

	auto consumed = lexingState->scan(character);
	if (consumed)
	{
		update_position(character);
	}
	return consumed;
}

HTMLLexer::~HTMLLexer()
{
	if (stream_holder)
	{
		delete stream_holder;
	}
}
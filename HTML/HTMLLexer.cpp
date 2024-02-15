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
		bool consumed;

		char to_scan;
		
		stream_holder->stream.get(to_scan);
		if (stream_holder->stream.eof())
		{
			to_scan = '\0';
		}

		consumed = lexing_state->scan(to_scan);
		if (!consumed)
		{
			stream_holder->stream.putback(to_scan);
		}
		else
		{
			update_position(to_scan);
		}
	}
	auto token = std::move(token_buffer.front());
	token_buffer.pop();
	return token;
}

bool HTMLLexer::read(const char character)
{
	auto lexing_state = std::static_pointer_cast<LexingState>(current_state);

	auto consumed = lexing_state->scan(character);
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
#include <memory>
#include "UrlLexer.h"
#include "UrlLexStartState.h"

UrlLexer::UrlLexer(const std::string& input) : source(input) 
{
	source_caret = 0;
	auto first_state = std::make_shared<UrlLexStartState>();
	transition(first_state);
}

unique_ptr<Token> UrlLexer::next()
{
	if (token_buffer.size() != 0)
	{
		auto token = std::move(token_buffer.front());
		token_buffer.pop();
		return token;
	}

	while (token_buffer.size() == 0)
	{
		auto lexing_state = std::static_pointer_cast<LexingState>(current_state);
		bool consumed;

		char to_scan;
		if (source_caret >= source.length())
		{
			to_scan = '\0';
		}
		else
		{
			to_scan = source[source_caret];
		}

		consumed = lexing_state->scan(to_scan);
		if (consumed)
		{
			source_caret++;
		}
	}
	auto token = std::move(token_buffer.front());
	token_buffer.pop();
	return token;
}
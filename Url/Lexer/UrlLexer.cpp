#include <memory>
#include "UrlLexer.h"
#include "../../LexingState.h"
#include "../../LexingScanResult.h"
#include "UrlLexStartState.h"

UrlLexer::UrlLexer(std::string& input) : source(input) 
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


	auto lexing_state = std::static_pointer_cast<LexingState>(current_state);
	LexingScanResult result;

	while (token_buffer.size() == 0)
	{
		if (source_caret >= source.length())
		{
			auto eof = std::make_unique<Token>();
			eof->type = StdTokenType::end;
			return eof;
		}
		else
		{
			result = lexing_state->scan(source[source_caret]);
			if (result.consumed)
			{
				source_caret++;
			}
		}
	}
	auto token = std::move(token_buffer.front());
	token_buffer.pop();
	return token;
}
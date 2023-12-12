#include "UrlParser.h"
#include "UrlParseStartState.h"

UrlParser::UrlParser(Url& out) : url(out)
{
	auto first_state = std::make_shared<UrlParseStartState>();
	transition(first_state);
}

unique_ptr<Token> UrlParser::scan(unique_ptr<Token> token)
{
	auto parsing_state = std::static_pointer_cast<ParsingState>(current_state);
	return parsing_state->scan(std::move(token));
}
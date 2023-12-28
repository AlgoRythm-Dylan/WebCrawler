#include "HTMLParser.h"

#include "HTMLParseStartState.h"

HTMLParser::HTMLParser(HTMLDocument& d) : document(d)
{
	current_state = unique_ptr<State>(new HTMLParseStartState());
	current_state->machine = this;
}

unique_ptr<Token> HTMLParser::scan(unique_ptr<Token> token)
{
	auto parsing_state = std::static_pointer_cast<ParsingState>(current_state);
	return parsing_state->scan(std::move(token));
}
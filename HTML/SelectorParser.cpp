#include "SelectorParser.h"

#include <ParsingState.h>

SelectorParser::SelectorParser(HTMLSelector& s) : selector(s)
{
	current_rule = nullptr;
}

unique_ptr<Token> SelectorParser::scan(unique_ptr<Token> token)
{
	auto parsing_state = std::static_pointer_cast<ParsingState>(current_state);
	return parsing_state->scan(std::move(token));
}
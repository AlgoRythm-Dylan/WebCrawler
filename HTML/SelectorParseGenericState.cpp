#include "SelectorParseGenericState.h"

#include <StringToken.h>

#include "SelectorParser.h"

unique_ptr<Token> SelectorParseGenericState::scan(unique_ptr<Token> token)
{
	auto parser = (SelectorParser*)machine;
	if (token->type == StdTokenType::str)
	{
		// This is a tag name
		auto sToken = (StringToken*)token.get();
		// Can do check if current tag name is empty. If not,
		// throw unexpected token
	}
	else if (token->type == StdTokenType::whitespace)
	{
		// Whitespace separates rules
		auto currentRulePtr = parser->current_rule.lock();
		// I count 'em
		auto newRule = std::make_shared<HTMLSelectorRule>();
		if (!currentRulePtr)
		{
			
			parser->selector.rules.push_back(newRule);
		}
	}
	return nullptr;
}
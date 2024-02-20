#pragma once

#include <Parser.h>

#include "HTMLSelector.h"

class SelectorParser : public Parser
{
public:
	shared_ptr<HTMLSelectorRule> current_rule;
	HTMLSelector& selector;

	SelectorParser(HTMLSelector&);

	virtual unique_ptr<Token> scan(unique_ptr<Token>) override;
};


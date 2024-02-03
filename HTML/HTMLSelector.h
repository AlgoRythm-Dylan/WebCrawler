#pragma once

#include <vector>

#include "HTMLSelectorRule.h"

using std::vector;

class HTMLSelector
{
public:
	// List of rules is executed as OR
	// match = rule[0] OR rule[1]
	vector<HTMLSelectorRule> rules;
};

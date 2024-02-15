#pragma once

#include <string>
#include <optional>

using std::string;
using std::optional;

struct AttributeRequirement
{
	bool value_case_sensitive = true;
	optional<string> value;
};
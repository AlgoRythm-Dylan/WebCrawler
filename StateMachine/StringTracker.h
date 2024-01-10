#pragma once

#include <string>
#include <string_view>

using std::string;
using std::string_view;

class StringTracker
{
public:
	string to_match, memory;
	bool is_case_insensitive = false;

	StringTracker();
	StringTracker(string_view);

	bool add(const char);
	bool is_match() const;
};

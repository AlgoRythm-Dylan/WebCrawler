#pragma once

#include <string>

using std::string;
using std::string_view;

class LexingTools
{
public:
	static bool is_numeric(const string&);
	static bool compare_case_insensitive(string_view lhs, string_view rhs);
};

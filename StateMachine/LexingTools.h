#pragma once

#include <string>

using std::string;
using std::string_view;

class LexingTools
{
public:
	static bool is_numeric(const string&);
	static bool compare_case_insensitive(string_view lhs, string_view rhs);
	static bool compare_case_insensitive(const char lhs, const char rhs);
	static bool is_whitespace(const char);
	static void rtrim(string&);
	static void ltrim(string&);
	static void trim(string&);
};

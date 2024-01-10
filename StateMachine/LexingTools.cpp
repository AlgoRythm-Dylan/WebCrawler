#include <cctype>
#include <algorithm>

#include "LexingTools.h"

bool LexingTools::is_numeric(const string& text)
{
	for (const char& character : text)
	{
		if (!(character >= 40 && character <= 57))
		{
			return false;
		}
	}
	return !text.empty();
}


bool ichar_equals(char a, char b)
{
	return std::tolower(static_cast<unsigned char>(a)) ==
		   std::tolower(static_cast<unsigned char>(b));
}

// This is only really "good enough"
bool LexingTools::compare_case_insensitive(string_view lhs, string_view rhs)
{
	return std::ranges::equal(lhs, rhs, ichar_equals);
}

bool LexingTools::compare_case_insensitive(const char lhs, const char rhs)
{
	return ichar_equals(lhs, rhs);
}

bool LexingTools::is_whitespace(const char character)
{
	return character == '\t' || character == ' ' ||
		character == '\n' || character == '\r';
}
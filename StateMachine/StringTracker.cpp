#include "StringTracker.h"

#include "LexingTools.h"

StringTracker::StringTracker() {}
StringTracker::StringTracker(string_view source) : to_match(source) {}

bool StringTracker::add(const char character)
{
	if (memory.size() == to_match.size())
	{
		memory = "";
		return false;
	}
	auto nextChar = to_match[memory.size()];
	bool match = false;
	if (is_case_insensitive)
	{
		match = LexingTools::compare_case_insensitive(character, nextChar);
	}
	else
	{
		match = character == nextChar;
	}
	if (match)
	{
		memory += nextChar;
		return true;
	}
	else
	{
		memory = "";
		return false;
	}
}

bool StringTracker::is_match() const
{
	if (is_case_insensitive)
	{
		return LexingTools::compare_case_insensitive(memory, to_match);
	}
	else
	{
		return memory == to_match;
	}
}
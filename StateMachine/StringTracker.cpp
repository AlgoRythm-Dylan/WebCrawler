#include "StringTracker.h"

#include "LexingTools.h"

StringTracker::StringTracker()
{
	match_position = 0;
}

StringTracker::StringTracker(string_view source) : to_match(source)
{
	match_position = 0;
}

bool StringTracker::add(const char character)
{
	if (match_position >= to_match.size())
	{
		// What should the behavior be? Reset?
		match_position = 0;
	}
	else
	{
		if (character == to_match[match_position])
		{
			match_position++;
			return true;
		}
		else
		{
			match_position = 0;
		}
	}
	return false;
}

bool StringTracker::is_match() const
{
	return match_position == to_match.size();
}
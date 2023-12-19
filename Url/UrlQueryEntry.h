#pragma once

#include <string>

using std::string;

class UrlQueryEntry
{
public:
	string key, value;

	UrlQueryEntry();
	UrlQueryEntry(string, string);
};


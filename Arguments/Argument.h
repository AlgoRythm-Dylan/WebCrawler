#pragma once

#include <map>
#include <string>

enum ArgumentType
{
	Positional,
	Flag,
	KeyValue
};

using std::map;
using std::string;

union ArgumentData
{
	map<string, string> data_map;
	string data_string;
};

struct Argument
{
	ArgumentType type;
	ArgumentData value;
};

#pragma once

#include <string>
#include <set>
#include <vector>
#include <memory>

using std::string;
using std::set;
using std::shared_ptr;

enum ArgumentType : unsigned char
{
	Flag,
	KeyValue,
	Positional
};

class Argument
{
public:
	bool required, value_required;
	set<char> short_flags;
	set<string> long_flags;
	ArgumentType type;
	string name, description;
	string default_value;

	Argument();

	static shared_ptr<Argument> flag();
	static shared_ptr<Argument> key_value();
};
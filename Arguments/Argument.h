#pragma once

#include <string>
#include <string_view>
#include <set>
#include <vector>
#include <memory>

using std::string;
using std::set;
using std::shared_ptr;
using std::vector;
using std::string_view;

enum ArgumentType : unsigned char
{
	Flag,
	KeyValue,
	Positional,
	KeyValueList
};

class Argument
{
public:
	// Attributes
	bool required, value_required;
	set<char> short_flags;
	set<string> long_flags;
	ArgumentType type;
	string name, description;
	string default_value;

	// Parse result variables
	string value;
	vector<string> values;
	bool is_set;

	Argument();

	static shared_ptr<Argument> flag();
	static shared_ptr<Argument> flag(char);
	static shared_ptr<Argument> flag(string_view);
	static shared_ptr<Argument> key_value();
	static shared_ptr<Argument> key_value(string_view);
	static shared_ptr<Argument> key_value_list();
	static shared_ptr<Argument> key_value_list(string_view);
};
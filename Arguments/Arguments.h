#pragma once

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <string_view>

#include "Argument.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::set;
using std::map;
using std::string_view;

/*

WebCrawler.exe --mode inspect "https://www.google.com/" -abc --colors=bright
ignored        key    value    positional index 0        flags k=v

*/

class Arguments
{
protected:
	set<string> flags;
	map<string, string> kv_args;
	vector<shared_ptr<Argument>> args;
public:
	void parse(int argc, const char* argv[]);
	vector<string> positionals;
	bool fail_on_unknown_flag;

	Arguments();

	void add_argument(shared_ptr<Argument>);
	bool flag_is_set(string_view);
};


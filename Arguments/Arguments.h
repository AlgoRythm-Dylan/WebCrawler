#pragma once

#include <string>
#include <vector>
#include <memory>
#include <string_view>

#include "Argument.h"
#include "SysArgStruct.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::string_view;

/*

WebCrawler.exe --mode inspect "https://www.google.com/" -abc --colors=bright
ignored        key    value    positional index 0        flags k=v

*/

class Arguments
{
protected:
	vector<shared_ptr<Argument>> args;
	shared_ptr<Argument> find_flag(string_view);
	shared_ptr<Argument> find_kv(string_view);
public:
	void parse(int argc, const char* argv[]);
	vector<string> positionals;
	bool fail_on_unknown_flag, fail_on_duplicate_value;

	Arguments();

	void add_argument(shared_ptr<Argument>);
	static unique_ptr<SysArgStruct> parse_from_string(string_view);
};

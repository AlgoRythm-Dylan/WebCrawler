#pragma once

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>

using std::string;
using std::vector;
using std::shared_ptr;
using std::set;
using std::map;

/*

WebCrawler.exe --mode inspect "https://www.google.com/" -abc --colors=bright
ignored        key    value    positional index 0        flags k=v


*/

class Arguments
{
public:
	void parse(int argc, const char* argv[]);
	set<string> flags;
	map<string, string> kv_args;
	vector<string> positionals;
};


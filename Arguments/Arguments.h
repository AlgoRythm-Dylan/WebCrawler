#pragma once

#include <string>
#include <vector>

#include "Argument.h"

using std::string;
using std::vector;

/*

WebCrawler.exe --mode inspect "https://www.google.com/" -abc --colors=bright
ignored        key    value    positional index 0        flags k=v


*/

class Arguments
{
public:
	vector<Argument> args;
	void parse(int argc, char* argv[]);
	string get(const string&);
	string get(int);
	bool is_flag_set();
};


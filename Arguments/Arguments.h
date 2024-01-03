#pragma once

#include <string>

using std::string;

class Arguments
{
public:
	void parse(int argc, char* argv[]);
	string get();
};


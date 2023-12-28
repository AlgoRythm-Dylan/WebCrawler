#pragma once

#include <string>
#include <istream>

using std::string;
using std::istream;

class HTMLDocument
{
public:
	string doctype;
	void parse(istream&);
};

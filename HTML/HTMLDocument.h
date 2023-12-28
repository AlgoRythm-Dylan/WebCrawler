#pragma once

#include <string>
#include <istream>

#include "HTMLNodeParent.h"

using std::string;
using std::istream;

class HTMLDocument : public HTMLNodeParent
{
public:
	string doctype;
	void parse(istream&);
};

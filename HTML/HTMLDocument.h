#pragma once

#include <string>
#include <istream>

#include "HTMLNode.h"

using std::string;
using std::istream;

class HTMLDocument : public HTMLNode
{
public:

	HTMLDocument();

	void parse(istream&);
};

#pragma once

#include <string>
#include <istream>

#include "HTMLNode.h"

using std::string;
using std::istream;

class HTMLDocument
{
public:

	HTMLDocument();

	shared_ptr<HTMLNode> root;
	void parse(istream&);
};

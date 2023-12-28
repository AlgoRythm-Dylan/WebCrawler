#pragma once

#include <string>
#include <istream>
#include <vector>
#include <memory>

#include "HTMLNode.h"

using std::string;
using std::istream;
using std::vector;
using std::shared_ptr;

class HTMLDocument
{
public:
	string doctype;
	void parse(istream&);
	vector<shared_ptr<HTMLNode>> children;
};

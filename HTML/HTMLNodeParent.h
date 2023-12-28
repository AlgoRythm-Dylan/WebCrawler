#pragma once

#include <vector>
#include <memory>
#include <string>

class HTMLNode;

using std::vector;
using std::shared_ptr;
using std::string;


// HTMLNodeParent is any HTML object which is
// a parent to HTMLNodes. This class will cover
// behavior that has to do with acting upon
// collections of HTML nodes, such as querying
class HTMLNodeParent
{
public:
	vector<shared_ptr<HTMLNode>> children;

	shared_ptr<HTMLNode> querySelector(string);
	vector<shared_ptr<HTMLNode>> querySelectorAll(string);
};

#include "HTMLNode.h"
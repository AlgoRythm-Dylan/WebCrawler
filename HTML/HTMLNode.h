#pragma once

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;

class HTMLNode
{
public:
	bool is_tag;
	string text_content;
	vector<shared_ptr<HTMLNode>> children;

	HTMLNode();
};


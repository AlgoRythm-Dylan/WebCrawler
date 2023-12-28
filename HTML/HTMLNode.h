#pragma once

#include <string>

#include "HTMLNodeParent.h"

using std::string;

class HTMLNode : public HTMLNodeParent
{
public:
	bool is_tag;
	string text_content;

	HTMLNode();
};


#pragma once

#include <string_view>

#include <ParsingState.h>

#include "HTMLNode.h"

using std::string_view;

class HTMLParseTagState : public ParsingState
{
protected:
	int counter;
	bool is_closing_tag, parsing_attribute_value, parsing_attribute_name;
	string attribute_name, closing_tag_name;
	void apply_attribute_name();
	shared_ptr<HTMLNode> find_opening_tag(string_view);
public:
	HTMLParseTagState();
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


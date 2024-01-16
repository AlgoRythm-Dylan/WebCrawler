#pragma once

#include <ParsingState.h>

class HTMLParseTagState : public ParsingState
{
protected:
	int counter;
	bool is_closing_tag, parsing_attribute_value, parsing_attribute_name;
	string attribute_name;
	void apply_attribute_name();
public:
	HTMLParseTagState();
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


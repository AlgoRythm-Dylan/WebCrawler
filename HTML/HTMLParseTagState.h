#pragma once

#include <ParsingState.h>

class HTMLParseTagState : public ParsingState
{
protected:
	int counter;
	bool is_closing_tag, parsing_attribute_value;
	string attribute_name;
public:
	HTMLParseTagState();
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


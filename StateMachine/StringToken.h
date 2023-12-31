#pragma once

#include <string>
#include "Token.h"

using std::string;

class StringToken : public Token
{
public:
	string value;

	StringToken();
	StringToken(string value);

	bool is_whitespace_only();
};


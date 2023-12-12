#include "StringToken.h"

StringToken::StringToken()
{
	type = StdTokenType::str;
}

StringToken::StringToken(string value)
{
	type = StdTokenType::str;
	this->value = value;
}
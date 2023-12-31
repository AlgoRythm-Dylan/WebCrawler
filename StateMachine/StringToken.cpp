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

bool StringToken::is_whitespace_only()
{
	for (auto& character : value)
	{
		if (character != ' ' && character != '\n' && character != '\r' && character != '\t')
		{
			return false;
		}
	}
	return true;
}
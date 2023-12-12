#pragma once
#include "StringToken.h"
class PunctuationToken : public StringToken
{
public:
	PunctuationToken();
	PunctuationToken(string value);
};

#include "PunctuationToken.h"

PunctuationToken::PunctuationToken()
{
	type = StdTokenType::punctuation;
}

PunctuationToken::PunctuationToken(string value)
{
	type = StdTokenType::punctuation;
	this->value = value;
}
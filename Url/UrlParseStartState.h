#pragma once

#include <ParsingState.h>

class UrlParseStartState : public ParsingState
{
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};

#pragma once
#include <ParsingState.h>
#include <iostream>

class UrlParseFragmentState : public ParsingState
{
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};

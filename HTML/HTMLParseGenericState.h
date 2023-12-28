#pragma once

#include <ParsingState.h>

class HTMLParseGenericState : public ParsingState
{
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


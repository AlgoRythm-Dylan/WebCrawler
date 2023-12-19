#pragma once

#include <ParsingState.h>

class UrlParsePathState : public ParsingState
{
protected:
	string memory;
	string complete_path;
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


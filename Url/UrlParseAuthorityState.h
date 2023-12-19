#pragma once

#include <vector>

#include <ParsingState.h>
#include <Token.h>

using std::vector;

class UrlParseAuthorityState : public ParsingState
{
protected:
	vector<unique_ptr<Token>> memory;
	void finish();
public:
	unique_ptr<Token> scan(unique_ptr<Token>);
};


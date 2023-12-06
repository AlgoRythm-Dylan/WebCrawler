#pragma once

#include "../../Parser.h"
#include "../../Url.h"

class UrlParser : public Parser
{
public:
	Url& url;

	UrlParser(Url&);

	unique_ptr<Token> scan(unique_ptr<Token>);
};


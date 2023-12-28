#pragma once

#include <Parser.h>

#include "HTMLDocument.h"

class HTMLParser : public Parser
{
public:
	HTMLDocument& document;

	HTMLParser(HTMLDocument&);
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


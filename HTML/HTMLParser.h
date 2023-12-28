#pragma once

#include <vector>

#include <Parser.h>

#include "HTMLDocument.h"
#include "HTMLParseNode.h"

using std::vector;

class HTMLParser : public Parser
{
public:
	HTMLDocument& document;
	vector<shared_ptr<HTMLParseNode>> node_stack;

	HTMLParser(HTMLDocument&);
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


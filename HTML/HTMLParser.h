#pragma once

#include <vector>

#include <Parser.h>

#include "HTMLDocument.h"
#include "HTMLNode.h"

using std::vector;

class HTMLParser : public Parser
{
public:
	HTMLDocument& document;
	shared_ptr<HTMLNode> current_node;

	HTMLParser(HTMLDocument&);
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};


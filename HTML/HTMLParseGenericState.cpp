#include "HTMLParseGenericState.h"

#include <StringToken.h>

#include "HTMLParser.h"
#include "HTMLNode.h"

unique_ptr<Token> HTMLParseGenericState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::str)
	{
		// Encountering a string in a generic state just means
		// we probably found a text node. So, we create a text node
		// and then add it to the children of the current node
		//
		// If the last node as also a text node (a node where
		// is_tag is false) then add it to that node!
		//
		// If the node stack is currently empty, that means
		// we're reading ont he current document itself,
		// so we just add a text node to the document instead

		auto node = std::make_shared<HTMLNode>();
		node->text_content = ((StringToken*)token.get())->value;

		auto parser = ((HTMLParser*)machine);

		// Push directly onto document for now...
		parser->document.children.push_back(node);
	}
	else if(token->type == StdTokenType::punctuation)
	{

	}
	return nullptr;
}
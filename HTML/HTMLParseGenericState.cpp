#include "HTMLParseGenericState.h"

#include <StringToken.h>
#include <PunctuationToken.h>

#include "HTMLParser.h"
#include "HTMLNode.h"
#include "HTMLElement.h"
#include "HTMLParseTagState.h"

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
		auto pToken = (PunctuationToken*)token.get();
		if (pToken->value == "<")
		{
			// Create a new tag on the stack and
			// transition to tag parsing state
			auto tag = std::make_shared<HTMLNode>(new HTMLElement());

			auto parser = ((HTMLParser*)machine);
			parser->current_node->append_child(tag);
			parser->current_node = tag;

			transition(new HTMLParseTagState());
		}
		else
		{
			// Emit it as a text node or add it
			// to the current text node!
		}
	}
	return nullptr;
}
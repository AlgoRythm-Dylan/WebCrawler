#include "HTMLParseGenericState.h"

#include <StringToken.h>
#include <PunctuationToken.h>

#include "HTMLParser.h"
#include "HTMLNode.h"
#include "HTMLParseTagState.h"

unique_ptr<Token> HTMLParseGenericState::scan(unique_ptr<Token> token)
{
	if (token->type == StdTokenType::str)
	{
		// Encountering a string in a generic state just means
		// we probably found a text node. So, we create a text node
		// and then add it to the children of the current node

		auto sToken = (StringToken*)token.get();

		if (!sToken->is_whitespace_only())
		{
			auto node = shared_ptr<HTMLNode>(HTMLNode::text());
			node->text_content = sToken->value;

			auto parser = ((HTMLParser*)machine);
			auto currentNodePtr = parser->current_node.lock();

			currentNodePtr->append_child(node);
			// This text node can't have children so it doesn't
			// become the current node
		}
	}
	else if(token->type == StdTokenType::punctuation)
	{
		auto pToken = (PunctuationToken*)token.get();
		if (pToken->value == "<")
		{
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
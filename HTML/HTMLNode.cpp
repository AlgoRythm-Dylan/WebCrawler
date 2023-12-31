#include "HTMLNode.h"

#include <LexingTools.h>

HTMLNode::HTMLNode()
{
	// Just default to text node type
	type = HTMLNodeType::Text;
}

void HTMLNode::append_child(shared_ptr<HTMLNode> node)
{
	children.push_back(node);
	// BUGBUG: precondition of shared_from_this is that an existing shared pointer of
	// the object must already exist. This is not true for the document type.
	node->parent_node = shared_from_this();
}

// There's no such thing as a "self-closing tag" in HTML.
// They're called void elements instead
bool HTMLNode::is_void_element() const
{
	if (tag_name.empty())
	{
		return false;
	}
	return LexingTools::compare_case_insensitive("!doctype", tag_name) ||
		   LexingTools::compare_case_insensitive("area", tag_name) ||
		   LexingTools::compare_case_insensitive("base", tag_name) ||
		   LexingTools::compare_case_insensitive("br", tag_name) ||
		   LexingTools::compare_case_insensitive("col", tag_name) ||
		   LexingTools::compare_case_insensitive("embed", tag_name) ||
		   LexingTools::compare_case_insensitive("hr", tag_name) ||
		   LexingTools::compare_case_insensitive("img", tag_name) ||
		   LexingTools::compare_case_insensitive("input", tag_name) ||
		   LexingTools::compare_case_insensitive("link", tag_name) ||
		   LexingTools::compare_case_insensitive("meta", tag_name) ||
		   LexingTools::compare_case_insensitive("source", tag_name) ||
		   LexingTools::compare_case_insensitive("track", tag_name) ||
		   LexingTools::compare_case_insensitive("wbr", tag_name);
}

bool HTMLNode::is_root() const
{
	return type == HTMLNodeType::Root;
}

shared_ptr<HTMLNode> HTMLNode::querySelector(string query)
{
	return nullptr;
}

vector<shared_ptr<HTMLNode>> HTMLNode::querySelectorAll(string query)
{
	vector<shared_ptr<HTMLNode>> results;
	return results;
}

HTMLNode* HTMLNode::element()
{
	auto node = new HTMLNode();
	node->type = HTMLNodeType::Element;
	return node;
}

HTMLNode* HTMLNode::comment()
{
	auto node = new HTMLNode();
	node->type = HTMLNodeType::Comment;
	return node;
}

HTMLNode* HTMLNode::text()
{
	auto node = new HTMLNode();
	node->type = HTMLNodeType::Text;
	return node;
}
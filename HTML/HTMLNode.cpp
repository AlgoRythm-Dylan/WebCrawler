#include "HTMLNode.h"

#include <algorithm>

#include <LexingTools.h>

bool InsensitiveCompare::operator() (const string& a, const string& b) const
{
	// Convert both strings to lowercase for case-insensitive comparison
	std::string a_lower = a;
	std::transform(a_lower.begin(), a_lower.end(), a_lower.begin(), ::tolower);

	std::string b_lower = b;
	std::transform(b_lower.begin(), b_lower.end(), b_lower.begin(), ::tolower);

	return a_lower < b_lower;
}

HTMLNode::HTMLNode()
{
	// Just default to text node type
	type = HTMLNodeType::Text;
	closing_tag_found = false;
}

void HTMLNode::append_child(shared_ptr<HTMLNode> node)
{
	children.push_back(node);
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

int HTMLNode::my_index()
{
	auto parentPtr = parent_node.lock();
	if (!parentPtr)
	{
		return -1;
	}
	int myIndex = -1;
	for (const auto& node : parentPtr->children)
	{
		myIndex++;
		if (node.get() == this)
		{
			break;
		}
	}
	return myIndex;
}

shared_ptr<HTMLNode> HTMLNode::next_sibling()
{
	auto parentPtr = parent_node.lock();
	if (!parentPtr)
	{
		return nullptr;
	}
	
	for (int cursor = my_index() + 1; cursor < parentPtr->children.size(); cursor++)
	{
		auto sibling = parentPtr->children[cursor];
		if (sibling->type == HTMLNodeType::Element)
		{
			return sibling;
		}
	}
	return nullptr;
}

shared_ptr<HTMLNode> HTMLNode::prev_sibling()
{
	auto parentPtr = parent_node.lock();
	if (!parentPtr)
	{
		return nullptr;
	}

	for (int cursor = my_index() - 1; cursor >= 0; cursor--)
	{
		auto sibling = parentPtr->children[cursor];
		if (sibling->type == HTMLNodeType::Element)
		{
			return sibling;
		}
	}
	return nullptr;
}

optional<string> HTMLNode::id()
{
	if (m_id.was_fetched())
	{
		return m_id.value();
	}
	else
	{
		optional<string> id;
		if (attributes.contains("id"))
		{
			id = attributes["id"];
		}
		m_id.set_value(id);
		return id;
	}
}
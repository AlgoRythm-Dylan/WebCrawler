#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

enum HTMLNodeType : unsigned char {
	Root,
	Text,
	Comment,
	Element
};

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;

class HTMLNode : public std::enable_shared_from_this<HTMLNode>
{
public:
	HTMLNodeType type;
	string text_content, tag_name;
	shared_ptr<HTMLNode> parent_node;
	vector<shared_ptr<HTMLNode>> children;
	map<string, string> attributes;

	/* ctor */
	HTMLNode();

	/* member functions */
	void append_child(shared_ptr<HTMLNode>);
	shared_ptr<HTMLNode> querySelector(string);
	vector<shared_ptr<HTMLNode>> querySelectorAll(string);
	bool is_void_element() const;
	bool is_root() const;

	/* static ctors */
	static HTMLNode* element();
	static HTMLNode* text();
	static HTMLNode* comment();
};
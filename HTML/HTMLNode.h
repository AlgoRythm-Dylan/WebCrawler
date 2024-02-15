#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <set>

#include "Cached.h"

enum HTMLNodeType : unsigned char {
	Root,
	Text,
	Comment,
	Element
};

using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::vector;
using std::map;
using std::optional;
using std::set;


struct InsensitiveCompare {
	bool operator() (const string& a, const string& b) const;
};

using CaseInsensitiveMap = map<string, string, InsensitiveCompare>;
using CaseInsensitiveSet = set<string, InsensitiveCompare>;

class HTMLNode : public std::enable_shared_from_this<HTMLNode>
{
protected:
	int my_index();
	Cached<optional<string>> m_id;
	Cached<shared_ptr<CaseInsensitiveSet>> m_classes;
public:
	HTMLNodeType type;
	string text_content, tag_name;
	weak_ptr<HTMLNode> parent_node;
	vector<shared_ptr<HTMLNode>> children;
	CaseInsensitiveMap attributes;
	bool closing_tag_found;

	/* ctor */
	HTMLNode();

	/* member functions */
	void append_child(shared_ptr<HTMLNode>);
	shared_ptr<HTMLNode> querySelector(string);
	vector<shared_ptr<HTMLNode>> querySelectorAll(string);
	bool is_void_element() const;
	bool is_root() const;
	shared_ptr<HTMLNode> next_sibling();
	shared_ptr<HTMLNode> prev_sibling();
	optional<string> id();
	shared_ptr<CaseInsensitiveSet> classes();

	/* static ctors */
	static HTMLNode* element();
	static HTMLNode* text();
	static HTMLNode* comment();
};
#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <map>

#include "HTMLNode.h"
#include "AttributeRequirement.h"

using std::shared_ptr;
using std::vector;
using std::optional;
using std::map;

enum RelativeRelationship
{
	Parent,
	ParentDirect,
	Preceding,
	Following
};

class HTMLSelectorRule;

class HTMLSelectorRule
{
public:
	optional<string> tag_name, id;
	optional<shared_ptr<HTMLSelectorRule>> relative;
	set<string> class_names;
	map<string, AttributeRequirement, InsensitiveCompare> attributes;
	RelativeRelationship relative_relationship;
	bool is_satisfied_by(const shared_ptr<HTMLNode>) const;
};

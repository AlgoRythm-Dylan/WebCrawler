#include "HTMLSelectorRule.h"

#include <LexingTools.h>

bool HTMLSelectorRule::is_satisfied_by(const shared_ptr<HTMLNode> node, const shared_ptr<HTMLNode> search_root) const
{
	// Null check first so the other operations can assume valid state
	if (!node)
	{
		return false;
	}
	// The operations performed here should be ordered by
	// a matrix of "how often will this check be the determining factor"
	// and "how expensive is this check"
	if (tag_name.has_value())
	{
		bool match = LexingTools::compare_case_insensitive(node->tag_name, tag_name.value());
		if (!match)
		{
			return false;
		}
	}
	if (id.has_value())
	{
		auto nodeId = node->id();
		if (nodeId.has_value())
		{
			bool match = LexingTools::compare_case_insensitive(nodeId.value(), id.value());
			if (!match)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	for (const auto& name : class_names)
	{
		if (!node->classes()->contains(name))
		{
			return false;
		}
	}
	for (const auto& attribute : attributes)
	{
		if (!node->attributes.contains(attribute.first))
		{
			// Attribute is not even present
			return false;
		}
		if (attribute.second.value.has_value())
		{
			if (attribute.second.value_case_sensitive)
			{
				if (attribute.second.value.value() != node->attributes[attribute.first])
				{
					// Attribute is present, but value does not match or does not match case
					return false;
				}
			}
			else
			{
				if (!LexingTools::compare_case_insensitive(attribute.second.value.value(), node->attributes[attribute.first]))
				{
					// Attribute is present, but value does not match
					return false;
				}
			}
		}
	}
	if (relative.has_value())
	{
		auto relativeRule = relative.value();
		if (relative_relationship == RelativeRelationship::ParentDirect)
		{
			auto nodeParent = node->parent_node.lock();
			if (!nodeParent || !relativeRule->is_satisfied_by(nodeParent))
			{
				return false;
			}
		}
		else if (relative_relationship == RelativeRelationship::Parent)
		{
			auto nodeParent = node->parent_node.lock();
			bool match = false;
			while (nodeParent && nodeParent->type == HTMLNodeType::Element)
			{
				if (relativeRule->is_satisfied_by(nodeParent))
				{
					match = true;
					break;
				}
				else
				{
					nodeParent = nodeParent->parent_node.lock();
					if (search_root)
					{
						// Don't go past the search root
						if (nodeParent == search_root)
						{
							break;
						}
					}
				}
			}
			if (!match)
			{
				return false;
			}
		}
		else if (relative_relationship == RelativeRelationship::Preceding)
		{
			auto precedingNode = node->prev_sibling();
			if (!precedingNode || !relativeRule->is_satisfied_by(precedingNode))
			{
				return false;
			}
		}
		else if (relative_relationship == RelativeRelationship::Following)
		{
			auto nextNode = node->next_sibling();
			if (!nextNode || !relativeRule->is_satisfied_by(nextNode))
			{
				return false;
			}
		}
	}
	return true;
}
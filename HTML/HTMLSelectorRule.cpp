#include "HTMLSelectorRule.h"

#include <LexingTools.h>

bool HTMLSelectorRule::is_satisfied_by(const shared_ptr<HTMLNode> node) const
{
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
	return true;
}
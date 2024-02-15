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
	if (!class_names.empty())
	{
		for (const auto& name : class_names)
		{
			if (!node->classes()->contains(name))
			{
				return false;
			}
		}
	}
	return true;
}
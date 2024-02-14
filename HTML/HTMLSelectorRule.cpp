#include "HTMLSelectorRule.h"

#include <LexingTools.h>

bool HTMLSelectorRule::is_satisfied_by(const shared_ptr<HTMLNode> node) const
{
	bool match = false;
	if (tag_name.has_value())
	{
		match = match && LexingTools::compare_case_insensitive(node->tag_name, tag_name.value());
	}
	if (id.has_value())
	{
		auto nodeId = node->id();
		if (nodeId.has_value())
		{
			match = match && LexingTools::compare_case_insensitive(nodeId.value(), id.value());
		}
		else
		{
			match = false;
		}
	}
	return match;
}
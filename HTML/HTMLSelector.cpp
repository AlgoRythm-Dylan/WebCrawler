#include "HTMLSelector.h"

bool HTMLSelector::is_satisfied_by(const shared_ptr<HTMLNode> node, const shared_ptr<HTMLNode> search_root) const
{
	for (const auto& rule : rules)
	{
		if (rule.is_satisfied_by(node, search_root))
		{
			return true;
		}
	}
	return false;
}
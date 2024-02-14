#include "HTMLSelector.h"

bool HTMLSelector::is_satisfied_by(shared_ptr<HTMLNode> node)
{
	for (const auto& rule : rules)
	{
		if (rule.is_satisfied_by(node))
		{
			return true;
		}
	}
	return false;
}
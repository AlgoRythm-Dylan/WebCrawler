#pragma once

#include <memory>

#include "HTMLNode.h"

using std::shared_ptr;

class HTMLQueryRule
{
	bool is_satisfied_by(const shared_ptr<HTMLNode>) const;
};

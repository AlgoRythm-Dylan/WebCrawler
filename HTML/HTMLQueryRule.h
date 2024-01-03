#pragma once

#include <memory>
#include <vector>

#include "HTMLNode.h"

using std::shared_ptr;
using std::vector;

class HTMLQueryRule
{
public:
	bool is_satisfied_by(const shared_ptr<HTMLNode>) const;
};

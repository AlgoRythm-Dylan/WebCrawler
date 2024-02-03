#pragma once

#include <vector>

#include "HTMLSelector.h"
#include "HTMLNode.h"

using std::vector;

vector<shared_ptr<HTMLNode>> execute_selector(const vector<HTMLNode>& nodes, const HTMLSelector& query);
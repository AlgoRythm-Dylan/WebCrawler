#pragma once

#include <vector>

#include "HTMLQuery.h"
#include "HTMLNode.h"

using std::vector;

vector<shared_ptr<HTMLNode>> execute_query(const vector<HTMLNode>& nodes, const HTMLQuery& query);
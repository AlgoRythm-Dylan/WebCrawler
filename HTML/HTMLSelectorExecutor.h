#pragma once

#include <vector>

#include "HTMLSelector.h"
#include "HTMLNode.h"

using std::vector;

vector<shared_ptr<HTMLNode>> execute_selector(shared_ptr<HTMLNode>, const HTMLSelector&);
void execute_selector_step(shared_ptr<HTMLNode>, const HTMLSelector&, vector<shared_ptr<HTMLNode>>&);
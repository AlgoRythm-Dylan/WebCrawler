#pragma once

#include <memory>

#include "HTMLNode.h"

/*

Not sure if this class is completely necessary yet.
This class allows me to make a vector of HTMLNodes
while also being able to store metadata about them
without that metadata ending up in the final result.

*/

class HTMLParseNode
{
public:
	shared_ptr<HTMLNode> node;
};


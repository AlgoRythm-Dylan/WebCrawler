#pragma once

#include <vector>

#include "HTMLQueryRule.h"

using std::vector;

/*

	Query: "head"
	Returns: any with tag name head

	Query: "head meta"
	Returns: any with tag name meta inside tag name head

	Query: "head > meta"
	Returns: any with tag name meta that is direct child
	         of tag with name head

	Query: "head > meta[charset]"
	Returns: any meta tags that are direct children of
	         head tags where the meta tag has a charset
			 attribute set

	Query: "head > meta[charset='utf-8']"
	Returns: any meta tags that are direct children of
	         head tags where the meta tag has an
			 attribute with the key of charset and the
			 value of "utf-8"

	Query: "head > meta[charset='utf-8'], p"
	Returns: any meta tags that are direct children of
			 head tags where the meta tag has an
			 attribute with the key of charset and the
			 value of "utf-8" ... or any p tags

	Query: "head > meta p"
	Returns: Any p tags that are children of meta tags
	         which are DIRECT children of head tags

	#id = id
	.class.class.class = nested classes


	head > meta[charset] p

	rule target: p (each rule has only one target)
	...TODO

*/

class HTMLQuery
{
public:
	// List of rules is executed as OR
	// match = rule[0] OR rule[1]
	vector<HTMLQueryRule> rules;
};

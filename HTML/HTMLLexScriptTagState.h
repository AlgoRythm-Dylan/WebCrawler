#pragma once

#include "HTMLStringMemoryState.h"
#include <StringTracker.h>

class HTMLLexScriptTagState : public HTMLStringMemoryState
{
protected:
	StringTracker end_tag_tracker;
public:
	HTMLLexScriptTagState();

	bool scan(const char) override;
};

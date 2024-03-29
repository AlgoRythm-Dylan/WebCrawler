#pragma once

#include "HTMLStringMemoryState.h"

class HTMLLexCommentState : public HTMLStringMemoryState
{
protected:
	int consecutive_dash_count;
public:
	HTMLLexCommentState();

	bool scan(const char) override;
};


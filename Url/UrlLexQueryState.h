#pragma once

#include <Token.h>
#include "UrlStringMemoryState.h"

class UrlLexQueryState : public UrlStringMemoryState
{
public:
	bool scan(const char) override;
};

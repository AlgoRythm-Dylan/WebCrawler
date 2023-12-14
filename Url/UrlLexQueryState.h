#pragma once

#include <Token.h>
#include "UrlStringMemoryState.h"

class UrlLexQueryState : public UrlStringMemoryState
{
public:
	LexingScanResult scan(const char) override;
};

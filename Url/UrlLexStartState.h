#pragma once

#include "UrlStringMemoryState.h"
#include <LexingScanResult.h>

class UrlLexStartState : public UrlStringMemoryState
{
public:
	LexingScanResult scan(const char) override;
};

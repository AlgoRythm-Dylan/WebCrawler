#pragma once

#include "UrlStringMemoryState.h"

class UrlLexPathState : public UrlStringMemoryState
{
public:
	LexingScanResult scan(const char) override;
};

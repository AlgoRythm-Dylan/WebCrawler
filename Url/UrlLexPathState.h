#pragma once

#include "UrlStringMemoryState.h"

class UrlLexPathState : public UrlStringMemoryState
{
public:
	bool scan(const char) override;
};

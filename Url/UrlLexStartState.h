#pragma once

#include "UrlStringMemoryState.h"

class UrlLexStartState : public UrlStringMemoryState
{
public:
	bool scan(const char) override;
};

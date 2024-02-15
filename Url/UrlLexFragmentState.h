#pragma once
#include "UrlStringMemoryState.h"
class UrlLexFragmentState : public UrlStringMemoryState
{
	bool scan(const char) override;
};

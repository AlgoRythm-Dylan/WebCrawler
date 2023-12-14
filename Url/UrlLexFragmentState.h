#pragma once
#include "UrlStringMemoryState.h"
class UrlLexFragmentState : public UrlStringMemoryState
{
	LexingScanResult scan(const char) override;
};

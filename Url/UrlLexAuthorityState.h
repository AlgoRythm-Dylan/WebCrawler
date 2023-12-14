#pragma once

#include <Token.h>
#include "UrlStringMemoryState.h"

using std::unique_ptr;

class UrlLexAuthorityState : public UrlStringMemoryState
{
public:
	LexingScanResult scan(const char) override;
};


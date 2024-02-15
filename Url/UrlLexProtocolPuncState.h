#pragma once

#include <LexingState.h>

class UrlLexProtocolPuncState : public LexingState
{
	bool scan(const char) override;
};

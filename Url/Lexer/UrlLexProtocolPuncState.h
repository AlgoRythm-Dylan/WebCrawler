#pragma once

#include "../../LexingState.h"

class UrlLexProtocolPuncState : public LexingState
{
	LexingScanResult scan(const char) override;
};

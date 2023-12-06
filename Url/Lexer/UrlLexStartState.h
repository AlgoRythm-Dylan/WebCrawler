#pragma once

#include "../../LexingState.h"
#include "../../LexingScanResult.h"

class UrlLexStartState : public LexingState
{
protected:
	string memory;
public:
	LexingScanResult scan(const char) override;
};


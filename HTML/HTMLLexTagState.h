#pragma once
#include "HTMLStringMemoryState.h"

class HTMLLexTagState : public HTMLStringMemoryState
{
protected:
	int counter;
	string token_memory, tag_name_memory;
	bool encountered_whitespace;
public:
	HTMLLexTagState();

	LexingScanResult scan(const char) override;
};


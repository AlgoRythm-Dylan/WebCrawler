#pragma once

#include <ParsingState.h>
#include "UrlQueryEntry.h"

class UrlParseQueryState : public ParsingState
{
protected:
	string key, value, last_punctuation_seen, complete_query;
	void emit_memory();
public:
	unique_ptr<Token> scan(unique_ptr<Token>) override;
};

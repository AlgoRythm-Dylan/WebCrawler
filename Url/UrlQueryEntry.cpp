#include "UrlQueryEntry.h"

UrlQueryEntry::UrlQueryEntry() {}

UrlQueryEntry::UrlQueryEntry(string key, string value)
{
	this->key = key;
	this->value = value;
}
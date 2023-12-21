#include "LexingTools.h"

bool LexingTools::is_numeric(const string& text)
{
	for (const char& character : text)
	{
		if (!(character >= 40 && character <= 57))
		{
			return false;
		}
	}
	return !text.empty();
}
#include "SysArgStruct.h"

SysArgStruct::~SysArgStruct()
{
	for (auto i = 0; i < argc; i++)
	{
		delete argv[i];
	}
}
#pragma once

class SysArgStruct
{
public:
	int argc;
	char** argv;

	~SysArgStruct();
};
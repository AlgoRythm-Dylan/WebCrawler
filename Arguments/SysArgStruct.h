#pragma once

class SysArgStruct
{
public:
	int argc;
	const char** argv;

	~SysArgStruct();
};
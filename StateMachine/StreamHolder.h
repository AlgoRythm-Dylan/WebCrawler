#pragma once

#include <istream>

using std::istream;

class StreamHolder
{
public:
	istream& stream;
	StreamHolder(istream&);
};


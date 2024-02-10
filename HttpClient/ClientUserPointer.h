#pragma once

#include <functional>

#include "HttpResponse.h"

using std::function;

struct ClientUserPointer
{
	function<void(char*, size_t)>& function;
	HttpResponse& response;
};
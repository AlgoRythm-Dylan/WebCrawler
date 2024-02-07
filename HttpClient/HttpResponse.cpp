#include "HttpResponse.h"

HttpResponse::HttpResponse()
{
	status = 0; // Not fetched / error
}

bool HttpResponse::is_success_status_code()
{
	return status <= 399;
}
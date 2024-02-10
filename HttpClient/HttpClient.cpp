#include "HttpClient.h"

#include <LexingTools.h>

#include "ClientUserPointer.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	// Re-interpret the user pointer as our data callback
	auto pointer = *reinterpret_cast<ClientUserPointer*>(userp);
	pointer.function((char*)contents, size*nmemb);
	pointer.response.response_size += size * nmemb;
	return size * nmemb;
}

static size_t HeaderCallback(char* buffer, size_t size, size_t nitems, void* userp)
{
	auto response = (HttpResponse*)userp;
	string completeHeader(buffer, size * nitems);
	int colonIndex = completeHeader.find(":");
	if (colonIndex != -1)
	{
		string lhs, rhs;
		lhs = completeHeader.substr(0, colonIndex);
		rhs = completeHeader.substr(colonIndex + 1);
		LexingTools::trim(lhs);
		LexingTools::trim(rhs);
		response->headers.push_back({ lhs, rhs });
	}
	else
	{
		LexingTools::trim(completeHeader);
		response->headers.push_back({ completeHeader, "" });
	}
	return size * nitems;
}

shared_ptr<HttpResponse> HttpClient::get(const string& url,
	function<void(char*, size_t)> dataCallback,
	function<void(shared_ptr<HttpResponse>)> finishCallback)
{
	auto response = std::make_shared<HttpResponse>();

	ClientUserPointer pointer = {
		dataCallback, *response
	};

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &pointer);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, response.get());
	if (!user_agent.empty())
	{
		curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
	}

	curl_easy_perform(curl);

	long returnCode;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &returnCode);
	response->status = returnCode;

	finishCallback(response);
	curl_easy_cleanup(curl);

	return response;
}
#include "HttpClient.h"

#include <LexingTools.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	// Re-interpret the user pointer as our data callback
	auto dataCallback = *reinterpret_cast<function<void(char*, size_t)>*>(userp);
	dataCallback((char*)contents, size*nmemb);
	return size * nmemb;
}

static size_t HeaderCallback(char* buffer, size_t size, size_t nitems, void* userp)
{
	auto response = (HttpResponse*)userp;
	string completeHeader(buffer, size * nitems);
	completeHeader = completeHeader;
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

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataCallback);
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
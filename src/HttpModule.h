#pragma once

#include "Common.h"
#include <curl/curl.h>

class HttpModule
{
public:
	HttpModule();
	~HttpModule();

	// Delete copy and move constructors
	HttpModule(const HttpModule&) = delete;
	HttpModule(HttpModule&&) = delete;

	// Delete copy and move assignments
	HttpModule& operator=(const HttpModule&) = delete;
	HttpModule& operator=(HttpModule&&) = delete;

	std::string GetForecast(std::string lon, std::string lat);

	inline std::string GetResponse() { return m_responseData; }

protected:
	std::string m_url;
	std::string m_city;

	std::string m_responseData;

private:
	static size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void* userData);
};
#include "HttpModule.h" 

HttpModule::HttpModule()
{
	std::cout << "HTTP Module Created!" << std::endl;
}

HttpModule::~HttpModule()
{
	std::cout << "HTTP Module Destroyed!" << std::endl;
}

std::string HttpModule::GetForecast(std::string lon, std::string lat)
{
	return std::string();
}

size_t HttpModule::WriteCallback(char* ptr, size_t size, size_t nmemb, void* userData)
{
	// Cast the userdata parameter to a string pointer
	std::string* response = reinterpret_cast<std::string*>(userData);

	// Append the response data to the string
	response->append(ptr, size * nmemb);

	size_t total_size = size * nmemb;

	return total_size;
}

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
	std::stringstream ss_final_url;
	ss_final_url << "http://api.openweathermap.org/data/2.5/onecall?lat=" << lat << "&lon=" << lon
		<< "&units=metric&exclude=current,minutely,hourly,alerts&appid=API_KEY";

	CURL* handle = curl_easy_init();
	if (handle == nullptr)
	{
		std::cout << "Failed to init CURL." << std::endl;
		curl_global_cleanup();
		return std::string();
	}

	curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(handle, CURLOPT_URL, ss_final_url.str().c_str());
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &HttpModule::WriteCallback);

	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &m_responseData);

	CURLcode result = curl_easy_perform(handle);
	if (result != CURLE_OK)
	{
		std::cerr << " Error : " << curl_easy_strerror(result) << std::endl;
	}
	else
	{
		// response
		std::cout << '\n' << '\n' << "==================================== Daily Forecast ====================================" << '\n' << '\n' << '\n';
		std::cout << m_responseData << std::endl;
	}

	curl_easy_cleanup(handle);
	curl_global_cleanup();
	return m_responseData;

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

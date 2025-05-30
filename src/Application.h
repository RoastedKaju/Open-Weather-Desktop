#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

#include <json/json.h>

#include "Common.h"



struct CitiesRowData
{
	CitiesRowData() : cityName(""), lon(0.0f), lat(0.0f), countryName("") {}
	std::string cityName;
	float lon;
	float lat;
	std::string countryName;
};

class Application
{
public:
	Application(GLFWwindow& window) : window{ window }
	{
		selectedCity = "None";
		selectedCountry = "None";
		selectedCityLatitude = "0.0";
		selectedCityLongitude = "0.0";
		ReadCityData("OpenWeatherAPI_Cities.csv");
		httpModule = std::make_unique<HttpModule>();
		requestResponse = "";
	};

	void Init();
	void NewFrame();
	void Update(GLFWwindow* window);
	void Render();
	void Shutdown();

	void AddCountryComboBox();
	void AddCityComboBox();
	void AddSelectedCityData();
	void AddForecastPlot();

	void ReadCityData(std::string pathToFile);

protected:
	GLFWwindow& window;

	// Map as in country (key) and cities vector as value.
	std::map < std::string, std::vector<std::tuple<std::string, std::string, std::string>>> country_to_cities_map;
	std::string selectedCountry;
	std::string selectedCity;
	std::string selectedCityLongitude;
	std::string selectedCityLatitude;

	std::unique_ptr<class HttpModule> httpModule;

	std::string requestResponse;
	Json::Value parsedJsonValue;

	double temps[7];

	float dayTemp;
	float morningTemp;
	float eveTemp;
	float nightTemp;

};
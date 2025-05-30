#include "Application.h"

#include "HttpModule.h"
#include "JsonModule.h"

void Application::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(&window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::NewFrame()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	int width, height;
	glfwGetWindowSize(&window, &width, &height);
	ImGui::SetNextWindowSize(ImVec2((float)width, (float)height));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
}

void Application::Update(GLFWwindow* window)
{
	ImGui::Begin("Open Weather GUI", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	AddCountryComboBox();
	AddCityComboBox();
	AddSelectedCityData();
	AddForecastPlot();
	ImGui::End();
}

void Application::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::Shutdown()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void Application::AddCountryComboBox()
{
	if (ImGui::BeginCombo("Country", selectedCountry.c_str()))
	{
		for (const auto& country : country_to_cities_map)
		{
			bool isSelected = (selectedCountry == country.first);
			if (ImGui::Selectable(country.first.c_str(), isSelected))
			{
				selectedCountry = country.first;
				// On selection changed reset the cities combo box
				selectedCity = "Select city.";
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

}

void Application::AddCityComboBox()
{
	if (ImGui::BeginCombo("City", selectedCity.c_str()))
	{
		// if the selected country exists in the map
		if (country_to_cities_map.find(selectedCountry) != country_to_cities_map.end())
		{
			for (const auto& entry : country_to_cities_map.at(selectedCountry))
			{
				std::string currentCity = std::get<0>(entry);
				selectedCityLongitude = std::get<1>(entry);
				selectedCityLatitude = std::get<2>(entry);

				bool bisSelected = (selectedCity == currentCity);
				if (ImGui::Selectable(currentCity.c_str(), bisSelected))
				{
					if (selectedCity != currentCity)
					{
						std::cout << "City Selected : " << currentCity << " :: " << selectedCityLongitude << ":" << selectedCityLatitude << std::endl;
						//httpModule.get()->GetLocation(lon, lat);
						HttpModule HTTPmodule;
						JsonModule JsonMod;
						requestResponse.clear();
						parsedJsonValue.clear();
						requestResponse = HTTPmodule.GetForecast(selectedCityLongitude, selectedCityLatitude);
						parsedJsonValue = JsonMod.ParseString(requestResponse);

						// Store the daily temperature in vector.
						std::cout << "Daily Temperatures :: " << std::endl;

						for (Json::ArrayIndex idx = 1; idx < parsedJsonValue["daily"].size(); ++idx)
						{
							float curr_temp = parsedJsonValue["daily"][idx]["temp"]["day"].asFloat();
							temps[idx - 1] = curr_temp;
						}

						// Today's temperature
						dayTemp = std::round(parsedJsonValue["daily"][0]["temp"]["day"].asFloat() * 100) / 100;
						morningTemp = std::round(parsedJsonValue["daily"][0]["temp"]["morn"].asFloat() * 100) / 100;
						eveTemp = std::round(parsedJsonValue["daily"][0]["temp"]["eve"].asFloat() * 100) / 100;
						nightTemp = std::round(parsedJsonValue["daily"][0]["temp"]["night"].asFloat() * 100) / 100;

					}
					selectedCity = currentCity;
				}
				if (bisSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
		}

		ImGui::EndCombo();
	}

}

void Application::AddSelectedCityData()
{
	ImGui::Text("Selected city details:");
	ImGui::LabelText("Longitude", selectedCityLongitude.c_str());
	ImGui::LabelText("Latitude", selectedCityLatitude.c_str());
	ImGui::LabelText("Time-zone", parsedJsonValue["timezone"].asString().c_str());
	//ImGui::LabelText("Weather Description", parsedJsonValue["daily"][0]["weather"][0]["description"].asString().c_str());
}

void Application::AddForecastPlot()
{
	double ticks[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	const char* xAxisLabels[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	//double yAxisTemp[] = { 20.2f, 18.0f, 22.1f, 15.0f, 16.0f, 27.0f, 30.0f };

	ImPlot::SetNextAxisLimits(ImAxis_X1, 0, 6);

	if (ImPlot::BeginPlot("Weather forecast", ImVec2(-1, 0)))
	{
		ImPlot::SetupAxisTicks(ImAxis_X1, ticks, 7, xAxisLabels, false);
		//ImPlot::PlotShaded("Shaded", ticks, temps, 7);
		ImPlot::PlotLine("Line Graph", ticks, temps, 7);
		ImPlot::EndPlot();
		ImPlot::SetNextAxisToFit(ImAxis_X1);
		ImPlot::SetNextAxisToFit(ImAxis_Y1);
	}

	ImGui::Text("Today's Weather");

	ImGui::LabelText("Morning Temperature", std::to_string(morningTemp).c_str());
	ImGui::LabelText("Day Temperature", std::to_string(dayTemp).c_str());
	ImGui::LabelText("Evening Temperature", std::to_string(eveTemp).c_str());
	ImGui::LabelText("Night Temperature", std::to_string(nightTemp).c_str());

}

void Application::ReadCityData(std::string pathToFile)
{
	std::ifstream file(pathToFile);

	if (!file.is_open())
	{
		std::cerr << "file not found!" << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // Read and discard the first row

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		CitiesRowData row;
		std::string column;
		std::vector<std::string> columns;

		while (std::getline(ss, column, ','))
		{
			columns.push_back(column);
		}

		// Set data in the unordered map
		country_to_cities_map[columns.at(3)].push_back(std::make_tuple(columns.at(0), columns.at(1), columns.at(2)));

	}

}

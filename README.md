﻿# ⛅ Open Weather Desktop

A Desktop weather application that connects to [OpenWeatherAPI](https://openweathermap.org) and reterives realtime weather data.

## 📦 Features

- Realtime weather data
- Graphical frontend with graphs
- Weather data for all countries and different cities

## 🛠️ Built With

- **Language**: C++
- **Build System**: [CMake](https://cmake.org)
- **Frontend**: [ImGui](https://github.com/ocornut/imgui), [ImPlot](https://github.com/epezent/implot)
- **Platform**: Windows

## 🚀 Getting Started

- Clone the repository along with it's submodules
- Go to Vendor/VCPKG and run **bootstrap-vcpkg.bat**
- Run **install_deps.bat** in the root directory
- Generate project files or open the folder with Visual Studio.

## 👨‍💻 API Key

You will need your own Open Weather API key for this project to work, once you got that all you need to do is replace the following with your own key:  
Inside the **HttpModule::GetForecast** function you will find this line:
```
s_final_url << "http://api.openweathermap.org/data/2.5/onecall?lat=" << lat << "&lon=" << lon
		<< "&units=metric&exclude=current,minutely,hourly,alerts&appid=API_KEY";
```  

Replace the **API_KEY** with your own._
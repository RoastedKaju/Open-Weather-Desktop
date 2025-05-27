cmake_minimum_required(VERSION 3.14)

# Project name
project(OpenWeatherDesktop LANGUAGES CXX)

# CXX version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executeable
add_executable(${PROJECT_NAME} "src/main.cpp" "src/HttpModule.h" "src/HttpModule.cpp" "src/Common.h" "src/JsonModule.h" "src/JsonModule.cpp")

# Find GLFW via VCPKG
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

# Add subdirectory for ImGUI
add_subdirectory(Vendor/ImGUI)

# Add subdirectory for ImPlot
add_subdirectory(Vendor/ImPlot)

# Link GLFW
target_link_libraries(${PROJECT_NAME} PRIVATE 
	glfw
	glad::glad
	OpenGL::GL
	imgui
	implot
	CURL::libcurl
	JsonCpp::JsonCpp)
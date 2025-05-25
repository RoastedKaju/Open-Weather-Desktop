# ImPlot static library make file

# Add all source files in IMPLOT_SOURCES variable
file(GLOB IMPLOT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Make static library called implot
add_library(implot STATIC ${IMPLOT_SOURCES})

# Directory where header files exist
target_include_directories(implot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(implot PUBLIC glfw OpenGL::GL imgui)
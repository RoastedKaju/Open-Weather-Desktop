# ImGUI static library make file

# Add all the source files in IMGUI_SROUCES variable
file(GLOB IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Make a static library called "imgui"
add_library(imgui STATIC ${IMGUI_SOURCES})

# directory where header files exist
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "HttpModule.h"
#include "JsonModule.h"
#include "Application.h"


void framebuffer_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	// Get a handle to the console window
	HWND consoleWnd = GetConsoleWindow();

	// Hide the console window
	ShowWindow(consoleWnd, SW_HIDE);

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenWeatherDesktop", nullptr, nullptr);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(window);

	if (window == nullptr)
	{
		glfwTerminate();
		std::cout << "failed to create glfw window." << std::endl;
		return EXIT_FAILURE;
	}

	// Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

	//UI app
	Application* frontend = new Application(*window);
	frontend->Init();

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		// process inputs
		process_inputs(window);
		// poll events
		glfwPollEvents();

		// set color
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		// UI
		frontend->NewFrame();
		frontend->Update(window);
		frontend->Render();

		// swap buffer
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	frontend->Shutdown();
	delete frontend;
	return EXIT_SUCCESS;
}

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW failed." << std::endl;
		return EXIT_FAILURE;
	}

	// Hints
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "my window", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Window is NULL" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Viewport
	glViewport(0, 0, 800, 600);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
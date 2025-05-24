#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

	// ImGUI example
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		// Generate new frame for ImGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowSize(ImVec2(800, 600));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		//Update ImGUI
		ImGui::Begin("Open Weather GUI", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::End();

		// Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
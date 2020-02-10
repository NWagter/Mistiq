#include "Mstqpch.h"
#include "GLFWWindow.h"
#include "include/glad/glad.h"
#include "imgui_impl_opengl3.h"

Mistiq::GLFWWindow::GLFWWindow() {
	m_Localization.LoadLanguageData();
}

Mistiq::GLFWWindow::~GLFWWindow() {
    
}

void Mistiq::GLFWWindow::Create(WindowProperties a_WindowProperties) {
	Window::Create(a_WindowProperties);

	glfwInit();
	m_IsOpen = true;
	m_Window = glfwCreateWindow(m_Properties.m_Width, m_Properties.m_Height, m_Properties.m_Name, nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowUserPointer(m_Window, &m_Properties);
	glfwSwapInterval(true);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

}

void Mistiq::GLFWWindow::Update(float a_DeltaTime) {
	glfwPollEvents();
	glfwSwapBuffers(m_Window);

	int x, y;
	glfwGetWindowSize(m_Window, &x, &y);
	m_Properties.m_Width = x;
	m_Properties.m_Height = y;
}

void Mistiq::GLFWWindow::Destroy() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Mistiq::GLFWWindow::IsOpen() {
	int state = glfwGetKey(m_Window, GLFW_KEY_ESCAPE);
	if (state == GLFW_PRESS)
	{
		m_IsOpen = false;
	}
	return m_IsOpen;
}

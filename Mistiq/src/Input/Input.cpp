#include "Mstqpch.h"
#include "Input.h"

Mistiq::Input::~Input()
{
	m_Window = nullptr;
}

bool Mistiq::Input::KeyPressed(int a_Key)
{
	if (glfwGetKey(m_Window, a_Key) == GLFW_PRESS) return true;
	return false;
}

bool Mistiq::Input::KeyReleased(int a_Key)
{
	if (glfwGetKey(m_Window, a_Key) == GLFW_RELEASE) return true;
	return false;
}

void Mistiq::Input::SetWindow(GLFWwindow* a_Window)
{
	m_Window = a_Window;
}

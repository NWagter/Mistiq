#include "Mstqpch.h"
#include "Window.h"

Mistiq::Window::Window() {

}

Mistiq::Window::~Window() {

}

void Mistiq::Window::Create(WindowProperties a_WindowProperties) {
	m_Properties = a_WindowProperties;
}

void Mistiq::Window::Update(float a_DeltaTime) {

}

void Mistiq::Window::Destroy() {

}

bool Mistiq::Window::IsOpen() {
	return false;
}

Mistiq::WindowProperties& Mistiq::Window::GetProperties() {
	return m_Properties;
}

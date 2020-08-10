#include "Mstqpch.h"
#include "Application.h"
#include <imgui.h>
#include "include/glad/glad.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture.h"


Mistiq::Application* Mistiq::Application::s_Instance = nullptr;

Mistiq::Application::Application()
{
	s_Instance = this;
}

Mistiq::Application::~Application()
{
    
}

void Mistiq::Application::Setup(std::shared_ptr<Application> a_Self) {
	m_Self = a_Self;
	///Setting up upper hierarchy engine classes
	m_Window = std::make_unique<GLFWWindow>(m_Self);
	m_GuiManager = std::make_unique<GUIManager>();
	m_ECSManager = std::make_unique<ECSManager>();
	m_Input = std::make_unique<Input>();

	///Setting up window
	WindowProperties windowProps;
	windowProps.m_Name = "Mistiq";
	windowProps.m_Width = 1920;
	windowProps.m_Height = 1080;
	m_Window->Create(windowProps);

    //Setting up input
	m_Input->SetWindow(m_Window->m_Window);
}

void Mistiq::Application::Update() {
	OPTICK_FRAME("ApplicationUpdate");

	float deltaTime = m_Timer.GetTimeAs();
	m_Timer.Reset();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_FPS = m_Window->m_FPS;

	m_ECSManager->UpdateSystems(deltaTime);
	m_GuiManager->Update(deltaTime, m_FPS);
	m_Window->Update(deltaTime);
}

void Mistiq::Application::Clean() {
	m_Window->Destroy();
}

bool Mistiq::Application::IsOpen() {
	return m_Window->IsOpen();
}

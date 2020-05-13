#include "Mstqpch.h"
#include "Application.h"
#include <imgui.h>
#include "include/glad/glad.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture.h";

Mistiq::Application::Application()
{
    ///Setting up upper hierarchy engine classes
	m_Window = std::make_unique<GLFWWindow>();
	m_GuiManager = std::make_unique<GUIManager>();
	m_ECSManager = std::make_unique<EntityManager>();
}

Mistiq::Application::~Application()
{
    
}

void Mistiq::Application::Setup() {
	///Setting up window
	WindowProperties windowProps;
	windowProps.m_Name = "Mistiq";
	windowProps.m_Width = 1920;
	windowProps.m_Height = 1080;
	m_Window->Create(windowProps);

	std::vector<std::shared_ptr<Mistiq::ModelData>> model = Mistiq::GLTFParser::Load("assets/models/Bomberman.gltf");

    for(int i = 0; i < model.size(); i++)
    {
		std::shared_ptr<GameObject> go = m_ECSManager->AddGameObject("GO");
		std::shared_ptr<MeshRenderer> meshComponent = std::make_shared<MeshRenderer>(model[i]);
		go->AddComponent(meshComponent);
		m_Window->allModels.push_back(meshComponent);
    }
}

void Mistiq::Application::Update() {
    OPTICK_FRAME("ApplicationUpdate")
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GuiManager->Update(0.2f);
	m_Window->Update(0.2f);


}

void Mistiq::Application::Clean() {
	m_Window->Destroy();
}

bool Mistiq::Application::IsOpen() {
	return m_Window->IsOpen();
}

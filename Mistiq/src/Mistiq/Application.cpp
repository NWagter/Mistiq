#include "Mstqpch.h"
#include "Application.h"
#include <imgui.h>
#include "include/glad/glad.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture.h";
#include "ECS/Components/Transform.h"


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

	//std::vector<std::shared_ptr<Mistiq::ModelData>> model = Mistiq::GLTFParser::Load("assets/models/Environment/TempEnvir.gltf");
	std::vector<std::shared_ptr<Mistiq::ModelData>> model = Mistiq::GLTFParser::Load("assets/models/Environment/Blockout/Blockout.gltf");

	for (int i = 0; i < model.size(); i++)
	{
		std::shared_ptr<GameObject> go = m_ECSManager->AddGameObject(model[i]->name);
		std::shared_ptr<Transform> transformComponent = std::make_shared<Transform>();
		go->AddComponent(transformComponent);

		transformComponent->SetPosition(glm::vec3(model[i]->node.translation[0], model[i]->node.translation[2] * -1, model[i]->node.translation[1]));
		transformComponent->SetRotation(glm::vec4(model[i]->node.rotation[0], model[i]->node.rotation[1], model[i]->node.rotation[2], 1.0f));
		transformComponent->SetScale(glm::vec3(model[i]->node.scale[0], model[i]->node.scale[1], model[i]->node.scale[2]));

		std::shared_ptr<MeshRenderer> meshComponent = std::make_shared<MeshRenderer>(model[i]);
		go->AddComponent(meshComponent);
		m_Window->allModels.push_back(meshComponent);
	}
	m_ECSManager->m_GameObjects[1]->GetComponent<MeshRenderer>()->enabled = false;
	m_Count = 0.0f;

	for (int i = 0; i < m_ECSManager->GetGameObjects().size(); i++) {
        if(m_ECSManager->GetGameObjects()[i]->GetName() != "rock_environment")
        {
			if (m_ECSManager->GetGameObjects()[i]->GetName() != "road_house")
			{
				//m_ECSManager->GetGameObjects()[i]->GetComponent<MeshRenderer>()->enabled = false;
			}
		}
    }
}

void Mistiq::Application::Update() {
    OPTICK_FRAME("ApplicationUpdate")
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ECSManager->Update(0.2f);
	m_GuiManager->Update(0.2f);
	m_Window->Update(0.2f);

	m_Count += m_Window->GetDeltaTime();

    /*for(int i = 0; i < m_ECSManager->GetGameObjects().size(); i++)
    {
		m_ECSManager->GetGameObjects()[i]->GetComponent<Transform>()->SetRotation(glm::vec4(
			m_ECSManager->GetGameObjects()[i]->GetComponent<Transform>()->GetRotation().x,
			m_ECSManager->GetGameObjects()[i]->GetComponent<Transform>()->GetRotation().y,
			m_ECSManager->GetGameObjects()[i]->GetComponent<Transform>()->GetRotation().z + 0.1f,
			m_ECSManager->GetGameObjects()[i]->GetComponent<Transform>()->GetRotation().w));
    }*/

    /*if(m_Count >= 3 && !m_Blink)
    {
		m_ECSManager->m_GameObjects[1]->GetComponent<MeshRenderer>()->enabled = true;
		m_ECSManager->m_GameObjects[0]->GetComponent<MeshRenderer>()->enabled = false;
		m_Count = 0;
		m_Blink = true;
    }
	else if (m_Count >= 1 && m_Blink)
	{
		m_ECSManager->m_GameObjects[1]->GetComponent<MeshRenderer>()->enabled = false;
		m_ECSManager->m_GameObjects[0]->GetComponent<MeshRenderer>()->enabled = true;
		m_Count = 0;
		m_Blink = false;
	}*/
}

void Mistiq::Application::Clean() {
	m_Window->Destroy();
}

bool Mistiq::Application::IsOpen() {
	return m_Window->IsOpen();
}

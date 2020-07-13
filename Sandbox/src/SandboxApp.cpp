#include "SandboxApp.h"
#include "ECS/Components/Transform.h"
#include "Grid.h"

#include "Graphics/ModelLoading/ModelLoader.h"

SandboxApp::SandboxApp()
{
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::Setup()
{
	Mistiq::Application::Setup();

    //Loading environment
	std::vector<std::shared_ptr<Mistiq::GameObject>> gameObjects = Mistiq::ModelLoader::InstantiateMultiple("assets/models/Environment/Blockout/Blockout2.gltf");

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		m_Window->allModels.push_back(gameObjects[i]->GetComponent<Mistiq::MeshRenderer>());
	}

    //Loading grid manager
	std::shared_ptr<Mistiq::GameObject> go = m_ECSManager->AddGameObject("GridManager");
	std::shared_ptr<Mistiq::Grid> gridComponent = std::make_shared<Mistiq::Grid>(13, 13, this);
	go->AddComponent(gridComponent);

	//Loading Bomberman character
	std::vector<std::shared_ptr<Mistiq::GameObject>> bomberman = Mistiq::ModelLoader::InstantiateMultiple("assets/models/Bomberman.gltf");

	for (int i = 0; i < bomberman.size(); i++)
	{
		bomberman[i]->GetComponent<Mistiq::Transform>()->SetTranslation(glm::vec3(-230.0f, 0, -230.0f));
		bomberman[i]->GetComponent<Mistiq::Transform>()->SetScale(glm::vec3(4, 4, 4));

		m_Window->allModels.push_back(bomberman[i]->GetComponent<Mistiq::MeshRenderer>());
		m_Player.push_back(bomberman[i]);
	}
}

void SandboxApp::Update()
{
	Mistiq::Application::Update();

    if(m_Input->KeyPressed(GLFW_KEY_A))
    {
		for (int i = 0; i < m_Player.size(); i++)
		{
			if (m_Player[0]->GetComponent<Mistiq::Transform>()->GetTranslation().z < 230)
			{
				m_Player[i]->GetComponent<Mistiq::Transform>()->SetTranslation(glm::vec3(
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().x,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().y,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().z + 1));
			}
			m_Player[i]->GetComponent<Mistiq::Transform>()->SetRotation(glm::vec4(90, 0, 0, 0));
		}
    }
	if (m_Input->KeyPressed(GLFW_KEY_D))
	{
		for (int i = 0; i < m_Player.size(); i++)
		{
            if(m_Player[0]->GetComponent<Mistiq::Transform>()->GetTranslation().z > -230)
            {
				m_Player[i]->GetComponent<Mistiq::Transform>()->SetTranslation(glm::vec3(
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().x,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().y,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().z - 1));
			}
			m_Player[i]->GetComponent<Mistiq::Transform>()->SetRotation(glm::vec4(90, 0, 180, 0));
		}
			
	}
	if (m_Input->KeyPressed(GLFW_KEY_W))
	{
		for (int i = 0; i < m_Player.size(); i++)
		{
            if(m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().x > -230.0f)
            {
				m_Player[i]->GetComponent<Mistiq::Transform>()->SetTranslation(glm::vec3(
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().x - 1,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().y,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().z));
            }
			m_Player[i]->GetComponent<Mistiq::Transform>()->SetRotation(glm::vec4(90, 0, 90, 0));
		}
	}
	if (m_Input->KeyPressed(GLFW_KEY_S))
	{
		for (int i = 0; i < m_Player.size(); i++)
		{
			if (m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().x < 230.0f)
			{
				m_Player[i]->GetComponent<Mistiq::Transform>()->SetTranslation(glm::vec3(
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().x + 1,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().y,
					m_Player[i]->GetComponent<Mistiq::Transform>()->GetTranslation().z));
			}
			
			m_Player[i]->GetComponent<Mistiq::Transform>()->SetRotation(glm::vec4(90, 0, 270, 0));
		}
	}
}

void SandboxApp::Clean()
{
	Mistiq::Application::Clean();
}

void main()
{
	SandboxApp* app = new SandboxApp();
	app->Setup();

    while(app->IsOpen()) {
		app->Update();
    }

	app->Clean();
	delete app;
}

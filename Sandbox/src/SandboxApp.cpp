#include "SandboxApp.h"
#include "Components.h"
#include "Systems.h"

#include "Graphics/ModelLoading/ModelLoader.h"

void SandboxApp::Setup(std::shared_ptr<Mistiq::Application> a_Self)
{
	Mistiq::Application::Setup(a_Self);
	Application::instance().m_ECSManager->AddComponentContainer<GridComponent>();

    //Loading environment
	Mistiq::ModelLoader::InstantiateMultiple("assets/models/Environment/Blockout/Blockout2.gltf");

    //Loading grid manager
	Mistiq::Entity& gridManager = m_ECSManager->AddEntity();
	Application::instance().m_ECSManager->AddComponent<GridComponent>(gridManager);
	std::shared_ptr<Grid> gridSystem = std::make_shared<Grid>();
	Application::instance().m_ECSManager->AddSystem(gridSystem);

	//Loading Bomberman character
	std::vector<Mistiq::Entity>& bomberman = Mistiq::ModelLoader::InstantiateMultiple("assets/models/Bomberman.gltf");

	for (int i = 0; i < bomberman.size(); i++)
	{
		Application::instance().m_ECSManager->GetComponentContainer<Mistiq::Location>()->Get(bomberman[i])->m_Translation = glm::vec3(-230.0f, 0, -230.0f);
		Application::instance().m_ECSManager->GetComponentContainer<Mistiq::Location>()->Get(bomberman[i])->m_Scale = glm::vec3(4, 4, 4);
		m_Player.push_back(bomberman[i]);
	}

	std::shared_ptr<Mistiq::MeshRenderer> renderer = std::make_shared<Mistiq::MeshRenderer>();
	Application::instance().m_ECSManager->AddSystem(renderer);
}

void SandboxApp::Update()
{
	Mistiq::Application::Update();
    /*
    if(m_Input->KeyPressed(GLFW_KEY_T))
    {
		for (int i = 0; i < m_Player.size(); i++)
		{
			Application::instance().m_ECSManager->RemoveGameObject(m_Player[i]);
		}
    }

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
    */
}

void SandboxApp::Clean()
{
	Mistiq::Application::Clean();
}

extern Mistiq::Application* Mistiq::CreateApplication();

void main()
{
	Mistiq::Application* app = Mistiq::CreateApplication();
	app->Setup(nullptr);

    while(app->IsOpen()) {
		app->Update();
    }

	app->Clean();
}

Mistiq::Application* Mistiq::CreateApplication()
{
	return new SandboxApp();
}
#include "SandboxApp.h"
#include "ECS/Components/Transform.h"
#include "Grid.h"

SandboxApp::SandboxApp()
{
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::Setup()
{
	Mistiq::Application::Setup();

#pragma region Loading environment
	std::vector<std::shared_ptr<Mistiq::ModelData>> model = Mistiq::GLTFParser::Load("assets/models/Environment/Blockout/Blockout2.gltf");

	for (int i = 0; i < model.size(); i++)
	{
		std::shared_ptr<Mistiq::GameObject> go = m_ECSManager->AddGameObject(model[i]->name);
		std::shared_ptr<Mistiq::Transform> transformComponent = std::make_shared<Mistiq::Transform>();
		go->AddComponent(transformComponent);

		transformComponent->SetTranslation(glm::vec3(model[i]->node.translation[0], model[i]->node.translation[2] * -1, model[i]->node.translation[1]));
		transformComponent->SetRotation(glm::vec4(90 + model[i]->node.rotation[0], model[i]->node.rotation[1], model[i]->node.rotation[2], 1.0f));
		transformComponent->SetScale(glm::vec3(model[i]->node.scale[0], model[i]->node.scale[1], model[i]->node.scale[2]));

		std::shared_ptr<Mistiq::MeshRenderer> meshComponent = std::make_shared<Mistiq::MeshRenderer>(model[i]);
		go->AddComponent(meshComponent);
		m_Window->allModels.push_back(meshComponent);
	}
#pragma endregion

	std::shared_ptr<Mistiq::GameObject> go = m_ECSManager->AddGameObject("GridManager");
	std::shared_ptr<Mistiq::Grid> gridComponent = std::make_shared<Mistiq::Grid>(13, 13, this);
	go->AddComponent(gridComponent);

	std::vector<std::shared_ptr<Mistiq::ModelData>> bomberman = Mistiq::GLTFParser::Load("assets/models/Bomberman.gltf");

	for (int i = 0; i < bomberman.size(); i++)
	{
		std::shared_ptr<Mistiq::GameObject> bombermanGo = m_ECSManager->AddGameObject(bomberman[i]->name);
		std::shared_ptr<Mistiq::Transform> transformComponent = std::make_shared<Mistiq::Transform>();
		bombermanGo->AddComponent(transformComponent);

		transformComponent->SetTranslation(glm::vec3(-230.0f, 0, -230.0f));
		transformComponent->SetRotation(glm::vec4(bomberman[i]->node.rotation[0], bomberman[i]->node.rotation[1], bomberman[i]->node.rotation[2], 1.0f));
		transformComponent->SetScale(glm::vec3(4, 4, 4));

		std::shared_ptr<Mistiq::MeshRenderer> meshComponent = std::make_shared<Mistiq::MeshRenderer>(bomberman[i]);
		bombermanGo->AddComponent(meshComponent);
		m_Window->allModels.push_back(meshComponent);
		m_Player.push_back(bombermanGo);
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

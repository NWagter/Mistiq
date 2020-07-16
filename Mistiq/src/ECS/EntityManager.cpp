#include "Mstqpch.h"
#include "EntityManager.h"
#include "Component.h"

Mistiq::EntityManager::EntityManager()
{

}

Mistiq::EntityManager::~EntityManager()
{

}

void Mistiq::EntityManager::Init(std::shared_ptr<Application> a_Application)
{
	m_Application = a_Application;
	m_GameObjectsID = 0;
}

void Mistiq::EntityManager::Start()
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Start();
	}
}

void Mistiq::EntityManager::Update(float a_DeltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Update(a_DeltaTime);
	}
}

std::shared_ptr<Mistiq::GameObject> Mistiq::EntityManager::AddGameObject(std::string a_Name)
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->SetID(m_GameObjectsID);
	go->Init(a_Name, nullptr);
	m_GameObjects.push_back(go);
	m_GameObjectsID++;

	//Adding Transform component by default
	//go->AddComponent<Transform>(false);

	return go;
}

std::shared_ptr<Mistiq::GameObject> Mistiq::EntityManager::AddGameObject(std::shared_ptr<GameObject> a_Go)
{
	m_GameObjects.push_back(a_Go);
	a_Go->SetID(m_GameObjectsID);
	a_Go->Init(a_Go->GetName(), nullptr);
	m_GameObjects.push_back(a_Go);
	m_GameObjectsID++;

	//Adding Transform component by default
	//a_Go->AddComponent<Transform>();

	return a_Go;
}

void Mistiq::EntityManager::RemoveGameObject(int a_Id)
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetID() == a_Id) {
			for (auto comp : (*it)->GetComponents())
			{
				//comp->OnRemoveComponent();
			}

			return;
		}
	}
}

std::vector<std::shared_ptr<Mistiq::GameObject>>& Mistiq::EntityManager::GetGameObjects()
{
	return m_GameObjects;
}

std::shared_ptr<Mistiq::Application> Mistiq::EntityManager::GetApplication()
{
	return m_Application;
}

std::shared_ptr<Mistiq::GameObject> Mistiq::EntityManager::GetGameObjectById(int a_Id)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetID() == a_Id)
		{
			return m_GameObjects[i];
		}
	}
	return nullptr;
}

std::shared_ptr<Mistiq::GameObject> Mistiq::EntityManager::GetGameObjectByName(std::string a_Name)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetName() == a_Name)
		{
			return m_GameObjects[i];
		}
	}
	return nullptr;
}

std::shared_ptr<Mistiq::GameObject> Mistiq::EntityManager::GetGameObjectByTag(std::string a_Tag)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetTag() == a_Tag)
		{
			return m_GameObjects[i];
		}
	}
	return nullptr;
}

void Mistiq::EntityManager::RemoveGameObject(std::string a_Name)
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetName() == a_Name) {
			for (auto comp : (*it)->GetComponents())
			{
				//comp->OnRemoveComponent();
			}
			return;
		}
	}
}

void Mistiq::EntityManager::RemoveGameObject(std::shared_ptr<GameObject> a_Go)
{
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it) == a_Go) {
			for (auto comp : (*it)->GetComponents())
			{
				//comp->OnRemoveComponent();
			}
			it->reset();
			a_Go.reset();
			m_GameObjects.erase(it);
			return;
		}
	}
	std::cout << std::endl;
}

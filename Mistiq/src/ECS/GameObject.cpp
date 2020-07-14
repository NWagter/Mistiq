#include "Mstqpch.h"
#include "GameObject.h"
#include "EntityManager.h"
#include "Component.h"
#include <json.hpp>

#include "Mistiq/Application.h"

Mistiq::GameObject::GameObject()
{

}

Mistiq::GameObject::~GameObject()
{
	m_Tag = "Undefined";
}

void Mistiq::GameObject::Init(std::string a_Name, std::shared_ptr<EntityManager> a_EntityManager)
{
	m_Name = a_Name;
	m_Tag = "Undefined";
	m_Enabled = false;
	m_EntityManager = a_EntityManager;
}

void Mistiq::GameObject::Start()
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Awake();
	}

	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Start();
	}
}

void Mistiq::GameObject::Update(float a_DeltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if (m_Components[i]->GetEnabled())
		{
			m_Components[i]->Update(a_DeltaTime);
		}
	}
}

std::shared_ptr<Mistiq::Component> Mistiq::GameObject::AddComponent(std::shared_ptr<Component> a_Comp)
{
	a_Comp->SetOwnerID(shared_from_this());
	m_ComponentsIDs++;
	m_Components.push_back(a_Comp);
	a_Comp->SetComponentID(m_ComponentsIDs);
	a_Comp->Awake();
	a_Comp->Start();
	return a_Comp;
}

std::shared_ptr<Mistiq::Component> Mistiq::GameObject::AddComponentLoadedIn(std::shared_ptr<Component> a_Comp)
{
	a_Comp->SetOwnerID(shared_from_this());
	CallBaseAddComponent(a_Comp);
	return a_Comp;
}

void Mistiq::GameObject::RemoveComponentEventBased(std::shared_ptr<Component> a_Comp)
{
	for (int i = 0; i < m_Components.size(); i++)
	{
		if (a_Comp->GetComponentID() == m_Components[i]->GetComponentID())
		{
			CallBaseRemoveComponent(m_Components[i], i);
		}
	}
}

void Mistiq::GameObject::RemoveComponent(std::shared_ptr<Component> a_Comp)
{
	for (int i = 0; i < m_Components.size(); i++)
	{
		if (a_Comp->GetComponentID() == m_Components[i]->GetComponentID())
		{
			CallBaseRemoveComponent(m_Components[i], i);
		}
	}
}

std::string Mistiq::GameObject::SetName(std::string a_Name)
{
	m_Name = a_Name;
	return m_Name;
}

std::string Mistiq::GameObject::GetName()
{
	return m_Name;
}

int Mistiq::GameObject::SetID(int a_ID)
{
	m_ID = a_ID;
	return m_ID;
}

int Mistiq::GameObject::GetID()
{
	return m_ID;
}

std::string Mistiq::GameObject::SetTag(std::string a_Tag)
{
	m_Tag = a_Tag;
	return m_Tag;
}

std::string Mistiq::GameObject::GetTag()
{
	return m_Tag;
}

bool Mistiq::GameObject::SetEnabled(bool a_Enabled)
{
	m_Enabled = a_Enabled;
	return m_Enabled;
}

bool Mistiq::GameObject::GetEnabled()
{
	return m_Enabled;
}

std::vector<std::shared_ptr<Mistiq::Component>> Mistiq::GameObject::GetComponents()
{
	return m_Components;
}

std::vector<std::shared_ptr<Mistiq::Mesh>> Mistiq::GameObject::GetRendererComponents()
{
	return m_RendererComponents;
}

std::shared_ptr<Mistiq::EntityManager> Mistiq::GameObject::GetEntityManager()
{
	return m_EntityManager;
}

void Mistiq::GameObject::CallBaseAddComponent(std::shared_ptr<Component> a_Comp)
{
	a_Comp->SetOwnerID(shared_from_this());
	a_Comp->Awake();
	a_Comp->Start();
}

void Mistiq::GameObject::CallBaseRemoveComponent(std::shared_ptr<Component> a_Comp, int a_Index)
{
	m_Components.erase(m_Components.begin() + a_Index);
}
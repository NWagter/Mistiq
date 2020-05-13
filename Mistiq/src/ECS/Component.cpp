#include "Mstqpch.h"
#include "Component.h"
#include "GameObject.h"
#include "EntityManager.h"

Mistiq::Component::Component()
{

}

Mistiq::Component::~Component()
{

}

void Mistiq::Component::Init(std::shared_ptr<GameObject> a_Owner, int a_ComponentID, bool a_OverwriteComponentID)
{
	m_OwnerId = a_Owner->GetID();

	if (a_OverwriteComponentID)
	{
		m_ComponentId = a_ComponentID;
	}

	m_Owner = a_Owner;
}

void Mistiq::Component::Awake()
{

}

void Mistiq::Component::Start()
{

}

void Mistiq::Component::Update(float a_DeltaTime)
{

}

bool Mistiq::Component::SetEnabled(bool a_Enabled)
{
	m_Enabled = a_Enabled;
	return m_Enabled;
}

bool Mistiq::Component::GetEnabled()
{
	return m_Enabled;
}

void Mistiq::Component::SetComponentID(int a_ComponentID)
{
	m_ComponentId = a_ComponentID;
}

void Mistiq::Component::SetOwnerID(std::shared_ptr<GameObject> a_Owner)
{
	m_Owner = a_Owner;
	m_OwnerId = a_Owner->GetID();
}

int Mistiq::Component::GetComponentID()
{
	return m_ComponentId;
}

int Mistiq::Component::GetOwnerID()
{
	return m_OwnerId;
}

std::shared_ptr<Mistiq::GameObject> Mistiq::Component::Owner()
{
	return m_Owner;
}

std::shared_ptr<Mistiq::EntityManager> Mistiq::Component::Creator()
{
	return m_Owner->GetEntityManager();
}

std::shared_ptr<Mistiq::GameObject> Mistiq::Component::AddGameObject(std::string a_Name)
{
	return m_Owner->GetEntityManager()->AddGameObject(a_Name);
}

std::shared_ptr<Mistiq::GameObject> Mistiq::Component::AddGameObject(std::shared_ptr<GameObject> a_Go)
{
	return m_Owner->GetEntityManager()->AddGameObject(a_Go);
}

std::shared_ptr<Mistiq::GameObject> Mistiq::Component::FindGameObjectByName(std::string a_Name)
{
	return m_Owner->GetEntityManager()->GetGameObjectByName(a_Name);
}

void Mistiq::Component::RemoveGameObject(int a_Id)
{
	m_Owner->GetEntityManager()->RemoveGameObject(a_Id);
}

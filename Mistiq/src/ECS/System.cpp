#include "Mstqpch.h"
#include "System.h"

Mistiq::System::System()
{
}

Mistiq::System::~System()
{
}

void Mistiq::System::Start()
{
}

void Mistiq::System::Update()
{
}

void Mistiq::System::AddEntity(Entity& entity)
{
	m_MatchingEntities.push_back(entity);
}

void Mistiq::System::RemoveEntity(Entity& entity)
{
	auto it = std::find(m_MatchingEntities.begin(), m_MatchingEntities.end(), entity);
	m_MatchingEntities.erase(it);
}

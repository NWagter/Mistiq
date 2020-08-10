#include "Mstqpch.h"
#include "ECSManager.h"
#include <algorithm>

Mistiq::ECSManager::ECSManager()
{
	m_EntityCount = 0;
}

Mistiq::ECSManager::~ECSManager()
{
}

Mistiq::Entity& Mistiq::ECSManager::AddEntity()
{
	++m_EntityCount;
	Entity entity = m_EntityCount;
	m_Entities.insert(std::pair<Entity, std::set<unsigned int>>(entity, {}));
	return m_EntityCount;
}

bool Mistiq::ECSManager::RemoveEntity(Entity& entity)
{
	auto it = m_Entities.find(entity);
	
    for(auto setIt : it->second)
    {
		m_Components[setIt]->Remove(entity);
    }
	it->second.clear();

	UnRegisterEntity(entity);
	m_Entities.erase(it);
	return true;
}

void Mistiq::ECSManager::UpdateSystems(float deltaTime)
{
    for(auto system : m_Systems)
    {
        system->Update();
    }
}

bool Mistiq::ECSManager::AddSystem(std::shared_ptr<System> system)
{
	m_Systems.push_back(system);

    for(auto it = m_Entities.begin(); it != m_Entities.end(); ++it)
    {
		Entity en = it->first;
		RegisterEntity(en);
    }
	return true;
}

bool Mistiq::ECSManager::RemoveSystem(std::shared_ptr<System> system)
{
	auto it = std::find(m_Systems.begin(), m_Systems.end(), system);
	m_Systems.erase(it);
	return true;
}

void Mistiq::ECSManager::RegisterEntity(Entity& entity)
{
	auto it = m_Entities.find(entity);
	std::set<unsigned int> entityComponents = it->second;
	for (auto s : m_Systems)
	{
		std::set<unsigned int> systemRequiredComponents = s->m_RequiredComponents;

		if (std::includes(entityComponents.begin(), entityComponents.end(), systemRequiredComponents.begin(), systemRequiredComponents.end()))
		{
			auto sIt = std::find(s->m_MatchingEntities.begin(), s->m_MatchingEntities.end(), it->first);

			if (sIt == s->m_MatchingEntities.end())
			{
				s->AddEntity(entity);
			}
		}
	}
}

void Mistiq::ECSManager::UnRegisterEntity(Entity& entity)
{
	auto it = m_Entities.find(entity);
	std::set<unsigned int> entityComponents = it->second;
	for (auto s : m_Systems)
	{
		std::set<unsigned int> systemRequiredComponents = s->m_RequiredComponents;

		auto sIt = std::find(s->m_MatchingEntities.begin(), s->m_MatchingEntities.end(), it->first);

		if (sIt != s->m_MatchingEntities.end())
		{
			if (!std::includes(entityComponents.begin(), entityComponents.end(), systemRequiredComponents.begin(), systemRequiredComponents.end())) {
				s->RemoveEntity(entity);
			}
		}
	}
}

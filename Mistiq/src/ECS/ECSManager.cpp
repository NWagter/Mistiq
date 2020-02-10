#include "Mstqpch.h"
#include "ECSManager.h"

Mistiq::ECSManager::ECSManager() {
	m_LastEntity = 0;
}

Mistiq::ECSManager::~ECSManager() {
}

Mistiq::Entity Mistiq::ECSManager::CreateEntity() {
	assert(m_LastEntity < std::numeric_limits<Entity>::max());
	m_Entities.insert(std::make_pair((m_LastEntity + 1), std::set<unsigned int>()));
	return (++m_LastEntity);
}

void Mistiq::ECSManager::RegisterEntity(const Entity a_Entity) {
	///If entity not found in existing entities then throw error
	auto entity = m_Entities.find(a_Entity);
	if (m_Entities.end() == entity) {
		throw std::runtime_error("The Entity does not exist");
	}


	auto entityComponents = (*entity).second;
	for (auto system = m_Systems.begin(); system != m_Systems.end(); ++system) {
		auto systemRequiredComponents = (*system)->GetRequiredComponents();
		if (std::includes(entityComponents.begin(), entityComponents.end(), systemRequiredComponents.begin(), systemRequiredComponents.end())) {
			(*system)->RegisterEntity(a_Entity);
		}
	}
}

void Mistiq::ECSManager::UnregisterEntity(const Entity a_Entity) {
	///If entity not found in existing entities then throw error
	auto entity = m_Entities.find(a_Entity);
	if (m_Entities.end() == entity) {
		throw std::runtime_error("The Entity does not exist");
	}

	//Else remove it
	for (auto system : m_Systems) {
		system->UnregisterEntity(a_Entity);
	}
}

void Mistiq::ECSManager::UpdateEntities(float a_DeltaTime) {
	for (auto system : m_Systems) {
		system->UpdateEntities(a_DeltaTime);
	}
}

#include "Mstqpch.h"
#include "System.h"

Mistiq::System::System()
{
	
}

Mistiq::System::~System()
{
}

void Mistiq::System::Setup(ECSManager* a_Manager) {
	m_Manager = a_Manager;
}

void Mistiq::System::UpdateEntities(float a_ElapsedTime) {

}

bool Mistiq::System::RegisterEntity(Entity a_Entity) {
	return m_MatchingEntities.insert(a_Entity).second;
}

void Mistiq::System::UnregisterEntity(Entity a_Entity) {
	m_MatchingEntities.erase(a_Entity);
}

bool Mistiq::System::HasEntity(Entity a_Entity) const {
	return (m_MatchingEntities.end() != m_MatchingEntities.find(a_Entity));
}

const std::set<unsigned>& Mistiq::System::GetRequiredComponents() const {
	return m_RequiredComponents;
}

void Mistiq::System::SetRequiredComponents(std::set<unsigned>&& a_RequiredComponents) {
	m_RequiredComponents = std::move(a_RequiredComponents);
}

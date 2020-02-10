#pragma once

#include "Entity.h"

namespace Mistiq {

	class ECSManager;

	class System {
	public:
		System();
		virtual ~System();

		void Setup(ECSManager* a_Manager);

		virtual void UpdateEntities(float a_ElapsedTime);

		bool RegisterEntity(Entity a_Entity);
		void UnregisterEntity(Entity a_Entity);
        bool HasEntity(Entity a_Entity) const;

		const std::set<unsigned int>& GetRequiredComponents() const;
	protected:
		void SetRequiredComponents(std::set<unsigned int>&& a_RequiredComponents);

	protected:
		std::set<Entity> m_MatchingEntities;
		ECSManager* m_Manager;

	private:
		std::set<unsigned int> m_RequiredComponents;
	};
}

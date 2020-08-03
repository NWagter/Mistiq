#pragma once
#include "Entity.h"

namespace Mistiq
{
	class System
	{
	public:
		System();
		virtual ~System();

		virtual void Start();
		virtual void Update();

		void AddEntity(Entity& entity);
		void RemoveEntity(Entity& entity);

	public:
		std::set<unsigned int> m_RequiredComponents;
		std::vector<Entity> m_MatchingEntities;
	};
}

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

		virtual void AddEntity(Entity& entity);
		virtual void RemoveEntity(Entity& entity);

	public:
		std::set<unsigned int> m_RequiredComponents;
		std::vector<Entity> m_MatchingEntities;
	};
}

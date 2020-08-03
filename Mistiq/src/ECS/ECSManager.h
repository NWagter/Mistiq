#pragma once
#include "Entity.h"
#include "Component.h"
#include "ComponentContainer.h"
#include "System.h"

#include <memory>

namespace Mistiq
{
	class ECSManager final
	{
	public:
		ECSManager();
		~ECSManager();

		Entity& AddEntity();
		bool RemoveEntity(Entity& entity);
		void UpdateSystems(float deltaTime);

		template<class C = Component>
		bool AddComponent(Entity& entity);

		template<class C = Component>
		bool RemoveComponent(Entity & entity);

		template<class C = Component>
		bool AddComponentContainer();
		template<class C = Component>
		void RemoveComponentContainer();
		template<class C = Component>
		std::shared_ptr<ComponentContainer<C>> GetComponentContainer();

		/*template<class S = System, typename ...Args>
		bool AddSystem(Args... args);*/
		bool AddSystem(std::shared_ptr<System> system);
		bool RemoveSystem(std::shared_ptr<System> system);

	private:
		void RegisterEntity(Entity& entity);
		void UnRegisterEntity(Entity& entity);

	private:
		std::map<Entity, std::set<unsigned int>> m_Entities;
		std::map<unsigned int, std::shared_ptr<BaseComponentContainer>> m_Components;
		std::vector<std::shared_ptr<System>> m_Systems;

		unsigned int m_EntityCount;
	};

	template <class C>
	bool Mistiq::ECSManager::AddComponent(Entity& entity)
	{
		std::shared_ptr<ComponentContainer<C>> container = std::dynamic_pointer_cast<ComponentContainer<C>>(m_Components.at(C::s_Type));
		std::shared_ptr<C> component = std::make_shared<C>();
		container->Add(entity, component);
		auto ent = m_Entities.find(entity);
		ent->second.insert(C::s_Type);
		RegisterEntity(entity);
		return true;
	}

	template <class C>
	bool Mistiq::ECSManager::RemoveComponent(Entity& entity)
	{
		std::shared_ptr<ComponentContainer<C>> container = m_Components.at(C::s_Type);
		container->Remove(entity);
		UnRegisterEntity(entity);
		return true;
	}

	template <class C>
	bool Mistiq::ECSManager::AddComponentContainer()
	{
		const std::shared_ptr<ComponentContainer<C>> container = std::make_shared<ComponentContainer<C>>();
		m_Components.insert(std::make_pair(C::s_Type, container));
		return true;
	}

	template <class C>
	void Mistiq::ECSManager::RemoveComponentContainer()
	{
		auto it = std::find(m_Components.begin(), m_Components.end(), C::s_Type);
		m_Components.erase(it);
	}

	template <class C>
	std::shared_ptr<Mistiq::ComponentContainer<C>> Mistiq::ECSManager::GetComponentContainer()
	{
		std::shared_ptr<BaseComponentContainer> container = m_Components.at(C::s_Type);
		std::shared_ptr<ComponentContainer<C>> container2 = std::dynamic_pointer_cast<ComponentContainer<C>>(container);
		return container2;
	}

	/*template <class S, typename ... Args>
	bool Mistiq::ECSManager::AddSystem(Args... args)
	{
		m_Systems.push_back(std::make_shared<S>(args));
		return true;
	}*/
}

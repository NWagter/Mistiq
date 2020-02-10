#pragma once

#include "Entity.h"
#include "Component.h"
#include "ComponentHolder.h"
#include "System.h"

namespace Mistiq {
	class ECSManager {
	public:
		ECSManager();
		~ECSManager();

        //Components
		template<typename T = Component, typename... Args>
		bool AddComponent(const Entity a_Entity, Args... a_Args);

        //Component storage
		template<typename T = Component>
		bool CreateComponentStorage();
		template<typename T = Component>
		std::shared_ptr<ComponentStore<T>> GetComponentStorage();

        //Systems
		template<typename T = System, typename... Args>
		void AddSystem(Args... a_Args);

        //Entities
		Entity CreateEntity();
		void RegisterEntity(const Entity a_Entity);
		void UnregisterEntity(const Entity a_Entity);

        //Updating entities
		void UpdateEntities(float a_DeltaTime);

	private:
		Entity m_LastEntity;
		std::unordered_map<Entity, std::set<unsigned int>> m_Entities;

		std::map<unsigned int, std::shared_ptr<ComponentBaseStorage>> m_ComponentStores;

		std::vector<std::shared_ptr<System>> m_Systems;
	};

    template <typename T, typename ... Args>
    bool ECSManager::AddComponent(const Entity a_Entity, Args... a_Args) {
		//When entity does not exist then throw an error
		auto entity = m_Entities.find(a_Entity);
		if (m_Entities.end() == entity) {
			throw std::runtime_error("The Entity does not exist");
		}

		//When no Component storage exist then create one
		auto compContainer = m_ComponentStores.find(T::m_Type);
		if (compContainer == m_ComponentStores.end()) {
			CreateComponentStorage<T>();
		}

		// Add the ComponentType to the Entity and component storage
		(*entity).second.insert(T::m_Type);
		std::shared_ptr<T> comp = std::make_shared<T>(a_Args ...);
		return GetComponentStorage<T>()->Add(a_Entity, std::move(comp));
	}

    template <typename T>
    bool ECSManager::CreateComponentStorage() {
        std::shared_ptr<ComponentStore<T>> componentStore = std::make_shared<ComponentStore<T>>();
		return m_ComponentStores.insert(std::make_pair(T::m_Type, componentStore)).second;
	}

    template <typename T>
	std::shared_ptr<ComponentStore<T>> ECSManager::GetComponentStorage() {
		auto iComponentStore = m_ComponentStores.find(T::m_Type);
		if (m_ComponentStores.end() == iComponentStore) {
			throw std::runtime_error("The Component storage does not exist");
		}
		return std::dynamic_pointer_cast<ComponentStore<T>>(iComponentStore->second);
	}

    template <typename T, typename ... Args>
    void ECSManager::AddSystem(Args... a_Args) {
		std::shared_ptr<System> system = std::make_shared<T>(a_Args ...);
		system->Setup(this);
		m_Systems.push_back(system);
	}
}

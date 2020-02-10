#pragma once

#include "Entity.h"
#include "Component.h"

namespace Mistiq {
	class ComponentBaseStorage {
	public:
        ComponentBaseStorage() {}
        virtual ~ComponentBaseStorage() {}
	};

	template<typename C = Component>
	class ComponentStore : public ComponentBaseStorage {
	public:
		ComponentStore();
		~ComponentStore();

		bool Add(const Entity a_Entity, std::shared_ptr<C> a_Component);
		bool Remove(Entity a_Entity);

		bool Has(Entity a_Entity);

		std::shared_ptr<C> Get(Entity a_Entity);
		const std::unordered_map<Entity, std::shared_ptr<C>>& GetComponents();

	private:
		std::unordered_map<Entity, std::shared_ptr<C>> m_Storage;
		static const unsigned int m_Type = C::m_Type;
	};

    template <typename C>
    ComponentStore<C>::ComponentStore() {

    }

    template <typename C>
    ComponentStore<C>::~ComponentStore() {
    }

    template <typename C>
    bool ComponentStore<C>::Add(const Entity a_Entity, std::shared_ptr<C> a_Component) {
		return m_Storage.insert(std::make_pair(a_Entity, std::move(a_Component))).second;
	}

    template <typename C>
    bool ComponentStore<C>::Remove(Entity a_Entity) {
		return (0 < m_Storage.erase(a_Entity));
	}

    template <typename C>
    bool ComponentStore<C>::Has(Entity a_Entity) {
		return (m_Storage.end() != m_Storage.find(a_Entity));
	}

    template <typename C>
    std::shared_ptr<C> ComponentStore<C>::Get(Entity a_Entity) {
		return m_Storage.at(a_Entity);
	}

    template <typename C>
    const std::unordered_map<Entity, std::shared_ptr<C>>& ComponentStore<C>::GetComponents() {
		return m_Storage;
	}
}

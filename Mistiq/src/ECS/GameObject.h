#pragma once
namespace Mistiq
{
	class Component;
	class EntityManager;
	class Mesh;

	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		~GameObject();

		template<class c = Component>
		void AddComponent(bool a_MakeEvent = false);
		std::shared_ptr<Component> AddComponent(std::shared_ptr<Component> a_Comp);

		template<class c = Component>
		void RemoveComponent();
		void RemoveComponent(std::shared_ptr<Component> a_Comp);

		template<class c = Component>
		std::shared_ptr<c> GetComponent();
		template<class c = Component>
		std::vector<std::shared_ptr<c>> GetComponents();

		std::string SetName(std::string a_Name);
		std::string GetName();

		int SetID(int a_ID);
		int GetID();

		std::string SetTag(std::string a_Tag);
		std::string GetTag();

		bool SetEnabled(bool a_Enabled);
		bool GetEnabled();

		std::vector<std::shared_ptr<Component>> GetComponents();
		std::vector<std::shared_ptr<Mesh>> GetRendererComponents();
		std::shared_ptr<EntityManager> GetEntityManager();

	private:
		void Init(std::string a_Name, std::shared_ptr<EntityManager> a_EntityManager);

		void Start();
		void Update(float a_DeltaTime);

		std::shared_ptr<Component> AddComponentLoadedIn(std::shared_ptr<Component> a_Comp);
		void RemoveComponentEventBased(std::shared_ptr<Component> a_Comp);

		void CallBaseAddComponent(std::shared_ptr<Component> a_Comp);
		void CallBaseRemoveComponent(std::shared_ptr<Component> a_Comp, int a_Index);

	private:
		std::string m_Name;
		int m_ID;
		std::string m_Tag;

		bool m_Enabled;

		int m_ComponentsIDs = 0;
		std::vector<std::shared_ptr<Component>> m_Components;
		std::vector<std::shared_ptr<Mesh>> m_RendererComponents;

		std::shared_ptr<EntityManager> m_EntityManager;

		friend class EntityManager;
		friend class EventManager;
		friend class EngineLoader;
	};

	template<class c>
	inline void GameObject::AddComponent(bool a_MakeEvent)
	{
		std::shared_ptr<Component> cast = std::make_shared<c>();
		m_ComponentsIDs++;
		a_Comp->SetComponentID(m_ComponentsIDs);
	}

	template <class c>
	void GameObject::RemoveComponent()
	{
		//TODO: Implement
	}

	template <class c>
	std::shared_ptr<c> GameObject::GetComponent()
	{
		for (int i = 0; i < m_Components.size(); i++) {
			//Try to dynamic cast input template to a Component
			std::shared_ptr<c> comp = std::dynamic_pointer_cast<c>(m_Components[i]);

			//If cast is correctly casted then add to Component vector
			if (comp) {
				return(comp);
			}
		}
		return nullptr;
	}

	template <class c>
	std::vector<std::shared_ptr<c>> GameObject::GetComponents()
	{
		//Make empty vector of Component pointers
		std::vector<std::shared_ptr<c>> components;

		//For Component size of map
		for (int i = 0; i < m_Components.size(); i++) {
			//Try to dynamic cast input template to a Component
			std::shared_ptr<Component> comp = dynamic_cast<std::shared_ptr<c>>(m_Components[i]);

			//If cast is correctly casted then add to Component vector
			if (comp) {
				components.push_back(comp);
			}
		}
		//Return the vector
		return components;
	}
}

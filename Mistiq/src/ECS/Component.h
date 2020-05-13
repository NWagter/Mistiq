#pragma once
#include "GameObject.h"
#include "EntityManager.h"

#define directx

namespace Mistiq
{
	class Component
	{
	public:
		Component();
		virtual ~Component();

		void Init(std::shared_ptr<GameObject> a_Owner, int a_ComponentID, bool a_OverwriteComponentID = true);

		virtual void Awake();
		virtual void Start();
		virtual void Update(float a_DeltaTime);

		bool SetEnabled(bool a_Enabled);
		bool GetEnabled();

		void SetComponentID(int a_ComponentID);
		void SetOwnerID(std::shared_ptr<GameObject> a_Owner);

		int GetComponentID();
		int GetOwnerID();
		std::shared_ptr<GameObject> Owner();

		std::shared_ptr<EntityManager> Creator();

		///These are here for creating and finding GameObjects through a component
		std::shared_ptr<GameObject> AddGameObject(std::string a_Name);
		std::shared_ptr<GameObject> AddGameObject(std::shared_ptr<GameObject> a_Go);
		std::shared_ptr<GameObject> FindGameObjectByName(std::string a_Name);

		void RemoveGameObject(int a_Id);

	private:
		bool m_Enabled;
		int m_ComponentId;

	protected:
		int m_OwnerId;
		std::shared_ptr<GameObject> m_Owner;
	};

}
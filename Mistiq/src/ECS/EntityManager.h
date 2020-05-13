#pragma once
#include <vector>

#include "GameObject.h"

namespace Mistiq
{
	class Component;
	class Application;

	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		std::shared_ptr<GameObject> AddGameObject(std::string a_Name);
		std::shared_ptr<GameObject> AddGameObject(std::shared_ptr<GameObject> a_Go);

		std::shared_ptr<GameObject> GetGameObjectById(int a_Id);
		std::shared_ptr<GameObject> GetGameObjectByName(std::string a_Name);
		std::shared_ptr<GameObject> GetGameObjectByTag(std::string a_Tag);

		void RemoveGameObject(int a_Id);
		void RemoveGameObject(std::string a_Name);
		void RemoveGameObject(std::shared_ptr<GameObject> a_Go);

		std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
		std::shared_ptr<Application> GetApplication();

		void Init(std::shared_ptr<Application> a_Application);

		void Start();
		void Update(float a_DeltaTime);

	private:
		///GameObjects 
		int m_GameObjectsID;
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;

		std::shared_ptr<Application> m_Application;

		friend class EngineLoader;
		friend class EventManager;
		friend class Application;
	};
}


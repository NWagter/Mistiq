#pragma once

namespace Mistiq
{
	class GameObject;

	class ModelLoader
	{
	public:
		static std::shared_ptr<GameObject> InstantiateOne(const char* a_PathToObject);
		static std::shared_ptr<GameObject> InstantiateOne(const char* a_PathToObject, glm::vec3 a_Pos);

		static std::vector<std::shared_ptr<GameObject>> InstantiateMultiple(const char* a_PathToObject);

	private:
		static std::vector<std::shared_ptr<GameObject>> BaseInstantiate(const char* a_PathToObject);
	};
}

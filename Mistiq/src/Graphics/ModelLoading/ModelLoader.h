#pragma once

namespace Mistiq
{
	class GameObject;

	class ModelLoader
	{
	public:
		static std::shared_ptr<GameObject> Instantiate(const char* a_PathToObject);
		static std::shared_ptr<GameObject> Instantiate(const char* a_PathToObject, glm::vec3 a_Pos);

	private:
		static std::shared_ptr<GameObject> BaseInstantiate(const char* a_PathToObject);
	};
}

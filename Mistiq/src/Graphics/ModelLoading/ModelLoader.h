#pragma once
#include "ECS/Entity.h"

namespace Mistiq
{
	class ModelLoader
	{
	public:
		static Entity& InstantiateOne(const char* a_PathToObject);
		static Entity& InstantiateOne(const char* a_PathToObject, glm::vec3 a_Pos);

		static std::vector<Entity>& InstantiateMultiple(const char* a_PathToObject);

	private:
		static std::vector<Entity> BaseInstantiate(const char* a_PathToObject);
	};
}

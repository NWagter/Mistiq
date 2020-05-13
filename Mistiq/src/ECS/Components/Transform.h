#pragma once
#include "ECS/Component.h"
#include "../../../ext/glm/glm/glm.hpp"

namespace Mistiq
{
	class Transform : public Mistiq::Component
	{
	public:
		Transform();
		~Transform();

		void Start() override;
		void Update(float a_DeltaTime) override;

		void SetPosition(glm::vec3 a_Position);
		void SetRotation(glm::vec3 a_Rotation);
		void SetScale(glm::vec3 a_Scale);

		glm::vec3& GetPosition();
		glm::vec3& GetRotation();
		glm::vec3& GetScale();

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}
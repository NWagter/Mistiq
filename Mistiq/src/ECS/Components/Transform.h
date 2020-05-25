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

		void SetTranslation(glm::vec3 a_Position);
		void SetRotation(glm::vec4 a_Rotation);
		void SetScale(glm::vec3 a_Scale);

		glm::vec3& GetTranslation();
		glm::vec4& GetRotation();
		glm::vec3& GetScale();

		glm::mat4 GetModelMatrix();

	private:
		void SetTranslationMatrix();
		void SetRotationMatrix();
		void SetScaleMatrix();

	private:
		glm::vec3 m_Translation;
		glm::vec4 m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_Model;
	};
}
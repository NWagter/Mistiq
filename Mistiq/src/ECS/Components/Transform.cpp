#include "Mstqpch.h"
#include "Transform.h"

Mistiq::Transform::Transform()
{
	m_Translation = glm::vec3();
	m_Rotation = glm::vec4();
	m_Scale = glm::vec3();
}

Mistiq::Transform::~Transform()
{
}

void Mistiq::Transform::Start()
{
}

void Mistiq::Transform::Update(float a_DeltaTime)
{
}

void Mistiq::Transform::SetTranslation(glm::vec3 a_Position)
{
	m_Translation = a_Position;
}

void Mistiq::Transform::SetRotation(glm::vec4 a_Rotation)
{
	m_Rotation = a_Rotation;
}

void Mistiq::Transform::SetScale(glm::vec3 a_Scale)
{
	m_Scale = a_Scale;
}

glm::vec3& Mistiq::Transform::GetTranslation()
{
	return m_Translation;
}

glm::vec4& Mistiq::Transform::GetRotation()
{
	return m_Rotation;
}

glm::vec3& Mistiq::Transform::GetScale()
{
	return m_Scale;
}

glm::mat4 Mistiq::Transform::GetModelMatrix()
{
	m_Model = glm::mat4(1.0f);
	SetTranslationMatrix();
	SetRotationMatrix();
	SetScaleMatrix();
	return m_Model;
}

void Mistiq::Transform::SetTranslationMatrix()
{
	m_Model = glm::translate(m_Model, glm::vec3(m_Translation.x, m_Translation.y, m_Translation.z));
}

void Mistiq::Transform::SetRotationMatrix()
{
	m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Mistiq::Transform::SetScaleMatrix()
{
	m_Model = glm::scale(m_Model, glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));
}

#include "Mstqpch.h"
#include "Transform.h"

Mistiq::Transform::Transform()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(0.1f, 0.1f, 0.1f);
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

void Mistiq::Transform::SetPosition(glm::vec3 a_Position)
{
	m_Position = a_Position;
}

void Mistiq::Transform::SetRotation(glm::vec3 a_Rotation)
{
	m_Rotation = a_Rotation;
}

void Mistiq::Transform::SetScale(glm::vec3 a_Scale)
{
	m_Scale = a_Scale;
}

glm::vec3& Mistiq::Transform::GetPosition()
{
	return m_Position;
}

glm::vec3& Mistiq::Transform::GetRotation()
{
	return m_Rotation;
}

glm::vec3& Mistiq::Transform::GetScale()
{
	return m_Scale;
}

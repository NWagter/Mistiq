#include "Mstqpch.h"
#include "Transform.h"

Mistiq::Transform::Transform()
{
	m_Position = glm::vec3();
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

void Mistiq::Transform::SetPosition(glm::vec3 a_Position)
{
	m_Position = a_Position;
}

void Mistiq::Transform::SetRotation(glm::vec4 a_Rotation)
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

glm::vec4& Mistiq::Transform::GetRotation()
{
	return m_Rotation;
}

glm::vec3& Mistiq::Transform::GetScale()
{
	return m_Scale;
}

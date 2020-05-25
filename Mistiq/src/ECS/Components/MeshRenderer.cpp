#include "Mstqpch.h"
#include "MeshRenderer.h"
#include "Transform.h"

void Mistiq::MeshRenderer::Start()
{
}

void Mistiq::MeshRenderer::Update(float a_DeltaTime)
{
	m_Translation = m_Owner->GetComponent<Transform>()->GetTranslation();
	m_Rotation = m_Owner->GetComponent<Transform>()->GetRotation();
	m_Scale = m_Owner->GetComponent<Transform>()->GetScale();
}

glm::mat4 Mistiq::MeshRenderer::GetModel()
{
	return m_Owner->GetComponent<Transform>()->GetModelMatrix();
}

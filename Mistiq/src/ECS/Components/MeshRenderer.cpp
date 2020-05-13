#include "Mstqpch.h"
#include "MeshRenderer.h"
#include "Transform.h"

void Mistiq::MeshRenderer::Start()
{
}

void Mistiq::MeshRenderer::Update(float a_DeltaTime)
{
	m_Position = m_Owner->GetComponent<Transform>()->GetPosition();
	m_Rotation = m_Owner->GetComponent<Transform>()->GetRotation();
	m_Scale = m_Owner->GetComponent<Transform>()->GetScale();
}

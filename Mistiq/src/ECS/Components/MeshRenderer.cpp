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

void Mistiq::MeshRenderer::MakeTranslationMatrix()
{
	mTranslationMatrix = glm::mat4(1.0f);
	mTranslationMatrix[3][0] = m_Position.x;
	mTranslationMatrix[3][1] = m_Position.y;
	mTranslationMatrix[3][2] = m_Position.z;
}

void Mistiq::MeshRenderer::MakeRotationMatrix()
{
	m_Rotation.x = m_Position.x + 90.0f;

	// set rotationx
	RotationMatrixX = glm::mat4(1.0f);
	RotationMatrixX[1][1] = cosf(m_Rotation.x);
	RotationMatrixX[2][1] = -sinf(m_Rotation.x);
	RotationMatrixX[1][2] = sinf(m_Rotation.x);
	RotationMatrixX[2][2] = cosf(m_Rotation.x);
	//set rotationy
	RotationMatrixY = glm::mat4(1.0f);
	RotationMatrixY[0][0] = cosf(m_Rotation.y);
	RotationMatrixY[2][0] = sinf(m_Rotation.y);
	RotationMatrixY[0][2] = -sinf(m_Rotation.y);
	RotationMatrixY[2][2] = cosf(m_Rotation.y);
	//set rotationz
	RotationMatrixZ = glm::mat4(1.0f);
	RotationMatrixZ[0][0] = cosf(m_Rotation.z);
	RotationMatrixZ[1][0] = -sinf(m_Rotation.z);
	RotationMatrixZ[0][1] = sinf(m_Rotation.z);
	RotationMatrixZ[1][1] = cosf(m_Rotation.z);

	// now the combined rotation   
	//mRotationMatrix = RotationMatrixX * RotationMatrixY * RotationMatrixZ;
	mRotationMatrix = RotationMatrixX * RotationMatrixY * RotationMatrixZ;
}

void Mistiq::MeshRenderer::MakeScaleMatrix()
{
	mScaleMatrix = glm::mat4(1.0f);
	mScaleMatrix = glm::scale(mScaleMatrix, m_Scale);
}

void Mistiq::MeshRenderer::MakeModelMatrix()
{
	Model = mTranslationMatrix * mRotationMatrix * mScaleMatrix;
}

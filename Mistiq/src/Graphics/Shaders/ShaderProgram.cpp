#include "Mstqpch.h"
#include "ShaderProgram.h"
#include "Shader.h"

Mistiq::ShaderProgram::ShaderProgram()
{
	m_ID = glCreateProgram();
}

void Mistiq::ShaderProgram::AddShader(std::shared_ptr<Shader> a_Shader)
{
	glAttachShader(m_ID, a_Shader->GetId());

}

void Mistiq::ShaderProgram::Link()
{
	glLinkProgram(m_ID);
}

void Mistiq::ShaderProgram::Use()
{
	glUseProgram(m_ID);
}

void Mistiq::ShaderProgram::SetBool(const std::string& a_Name, bool a_Value) const
{
	glUniform1i(glGetUniformLocation(m_ID, a_Name.c_str()), (int)a_Value);
}

void Mistiq::ShaderProgram::SetInt(const std::string& a_Name, int a_Value) const
{
	glUniform1i(glGetUniformLocation(m_ID, a_Name.c_str()), a_Value);
}

void Mistiq::ShaderProgram::setFloat(const std::string& a_Name, float a_Value) const
{
	glUniform1f(glGetUniformLocation(m_ID, a_Name.c_str()), a_Value);
}

const bool Mistiq::ShaderProgram::GetBool(const std::string& a_Name) const
{
	return 0;
}

const int Mistiq::ShaderProgram::GetInt(const std::string& a_Name) const
{
	return 0;
}

const float Mistiq::ShaderProgram::GetFloat(const std::string& a_Name) const
{
	return 0;
}

const int Mistiq::ShaderProgram::ID() const
{
	return m_ID;
}
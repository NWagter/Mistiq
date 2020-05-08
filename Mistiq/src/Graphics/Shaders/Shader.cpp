#include "Mstqpch.h"
#include "Shader.h"
#include "include/glad/glad.h"

Mistiq::Shader::Shader(const char* a_Path, ESHADER_TYPE a_Type) : m_Type(a_Type)
{
	std::string code;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(a_Path);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		code = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = code.c_str();
	switch (m_Type)
	{
	case SHADER_TYPE_VERTEX:
		m_ID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_ID, 1, &vShaderCode, NULL);
		glCompileShader(m_ID);
		break;
	case SHADER_TYPE_FRAGMENT:
		m_ID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_ID, 1, &vShaderCode, NULL);
		glCompileShader(m_ID);
		break;
	}
}

const Mistiq::Shader::ESHADER_TYPE Mistiq::Shader::GetType() const
{
	return m_Type;
}

const std::string& Mistiq::Shader::GetContent() const
{
	return m_Content;
}

const unsigned& Mistiq::Shader::GetId() const
{
	return m_ID;
}
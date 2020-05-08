#pragma once
#include "../../ext/Glad/include/glad//glad.h"
#include "../../ext/glm/glm/glm.hpp"
#include "../../ext/glm/glm/gtc/matrix_transform.hpp"
#include "../../ext/glm/glm/gtc/type_ptr.hpp"

namespace Mistiq
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram() = default;

		void AddShader(std::shared_ptr<Shader> a_Shader);
		void Link();
		void Use();

		void SetBool(const std::string& a_Name, bool a_Value) const;
		void SetInt(const std::string& a_Name, int a_Value) const;
		void setFloat(const std::string& a_Name, float a_Value) const;

		void setVec2(const std::string& name, const glm::vec2& value) const
		{
			glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
		}
		void setVec2(const std::string& name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
		}
		// ------------------------------------------------------------------------
		void setVec3(const std::string& name, const glm::vec3& value) const
		{
			glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
		}
		void setVec3(const std::string& name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
		}
		// ------------------------------------------------------------------------
		void setVec4(const std::string& name, const glm::vec4& value) const
		{
			glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
		}
		void setVec4(const std::string& name, float x, float y, float z, float w)
		{
			glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
		}
		// ------------------------------------------------------------------------
		void setMat2(const std::string& name, const glm::mat2& mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void setMat3(const std::string& name, const glm::mat3& mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void setMat4(const std::string& name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		const bool GetBool(const std::string& a_Name) const;
		const int GetInt(const std::string& a_Name) const;
		const float GetFloat(const std::string& a_Name) const;

		const int ID() const;

	private:
		unsigned int m_ID;
	};
}
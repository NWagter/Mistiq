#pragma once

namespace Mistiq
{
	/// @Vbrief Basic shader class
	class Shader
	{
	public:
		/// @Vbrief Enum to denote what type a shader is
		enum ESHADER_TYPE
		{
			SHADER_TYPE_VERTEX,
			SHADER_TYPE_FRAGMENT
		};

		Shader(const char* a_Path, ESHADER_TYPE a_Type);

		const ESHADER_TYPE GetType() const;
		const std::string& GetContent() const;
		const unsigned int& GetId() const;

	private:
		ESHADER_TYPE m_Type;
		std::string m_Content;
		unsigned int m_ID;
	};
}
#include "Mstqpch.h"
#include "Texture.h"

#include "../../ext/stb_image/stb_image.h"
#include "include/glad/glad.h"

Mistiq::Texture::Texture(const std::string& a_Path, bool a_HasAlpha) : m_Path(a_Path), m_HasAlpha(a_HasAlpha)
{
}

Mistiq::Texture::~Texture()
{
}

void Mistiq::Texture::Load()
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	//Wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_Data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
	if (m_Data)
	{
		if (m_HasAlpha)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture with path: " << m_Path << std::endl;
	}
	stbi_image_free(m_Data);
}

const unsigned Mistiq::Texture::ID() const
{
	return m_ID;
}
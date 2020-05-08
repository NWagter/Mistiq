#pragma once

namespace Mistiq
{
	class Texture
	{
	public:
		Texture(const std::string& a_Path, bool a_HasAlpha = false);
		~Texture();

		void Load();

		const unsigned int ID() const;
	private:
		std::string m_Path;

		int m_Width;
		int m_Height;
		int m_Channels;

		unsigned int m_ID;
		unsigned char* m_Data;

		bool m_HasAlpha;
	};
}
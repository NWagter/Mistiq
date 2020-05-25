#pragma once

namespace Mistiq {
	struct WindowProperties {
		char* m_Name;
		unsigned int m_Width;
		unsigned int m_Height;

		WindowProperties() {
			m_Name = "Window";
			m_Width = 1280;
			m_Height = 720;
		}
	};

	class Window {
	public:
		Window();
		virtual ~Window();

		virtual void Create(WindowProperties a_WindowProperties = WindowProperties(), bool a_VSync = false);
		virtual void Update(float a_DeltaTime);
		virtual void Destroy();

		virtual bool IsOpen();
		WindowProperties& GetProperties();

	protected:
		WindowProperties m_Properties;
	};
}

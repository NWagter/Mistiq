#pragma once

#include "Defines.h"
#include "WindowSystem/GLFWWindow.h"
#include "GUI/GUIManager.h"
#include "optick.h"

#include "../ECS/Component.h"

namespace Mistiq{
	/// @Vbrief Main application class for this application
	class Application {
	public:
		Application();
		virtual ~Application();

		/// @Vbrief Sets up application
		void Setup();
		/// @Vbrief Updates application
		void Update();
		/// @Vbrief Cleans the application after closing
		void Clean();

		/// @Vbrief Returns if the application is open or not
		bool IsOpen();

	private:
		/// @Vbrief Unique pointer to the window class of this application
		std::unique_ptr<GLFWWindow> m_Window;
		/// @Vbrief Unique pointer to the GUI manager of this application
		std::unique_ptr<GUIManager> m_GuiManager;

		std::unique_ptr<EntityManager> m_ECSManager;

		float m_Count;
		bool m_Blink;
	};
}

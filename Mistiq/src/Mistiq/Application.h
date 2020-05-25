#pragma once

#include "Defines.h"
#include "WindowSystem/GLFWWindow.h"
#include "GUI/GUIManager.h"
#include "optick.h"

#include "../ECS/Component.h"
#include "Input/Input.h"
#include "../Helpers/Timer.h"

namespace Mistiq{
	/// @Vbrief Main application class for this application
	class Application {
	public:
		Application();
		virtual ~Application();

		/// @Vbrief Sets up application
		virtual void Setup();
		/// @Vbrief Updates application
		virtual void Update();
		/// @Vbrief Cleans the application after closing
		virtual void Clean();

		/// @Vbrief Returns if the application is open or not
		bool IsOpen();

	public:
		/// @Vbrief Unique pointer to the window class of this application
		std::unique_ptr<GLFWWindow> m_Window;
		/// @Vbrief Unique pointer to the GUI manager of this application
		std::unique_ptr<GUIManager> m_GuiManager;

		std::unique_ptr<EntityManager> m_ECSManager;

		std::unique_ptr<Input> m_Input;

		Timer m_Timer;
		int m_FPS;
	};
}

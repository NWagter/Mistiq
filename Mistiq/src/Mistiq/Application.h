#pragma once

#include "Defines.h"
#include "WindowSystem/GLFWWindow.h"
#include "GUI/GUIManager.h"

namespace Mistiq{
	class MSTQ_API Application {
	public:
		Application();
		virtual ~Application();

		void Setup();
		void Update();
		void Clean();

		bool IsOpen();

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<GUIManager> m_GuiManager;
	};
}



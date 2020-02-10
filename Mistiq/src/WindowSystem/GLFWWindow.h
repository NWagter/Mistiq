#pragma once
#include "Window.h"
#include "imgui_impl_glfw.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
#include "../../vendor/imgui/imgui.h"
#include "../Localization/Localization.h"

namespace Mistiq {
	class GLFWWindow : public Window {
	public:
		GLFWWindow();
		~GLFWWindow();

        void Create(WindowProperties a_WindowProperties) override;
        void Update(float a_DeltaTime) override;
        void Destroy() override;

        bool IsOpen() override;

	public:
		GLFWwindow* m_Window;
		bool m_IsOpen;

	private:
	    float m_Time = 0.0f;

		Localization m_Localization;
	};
}

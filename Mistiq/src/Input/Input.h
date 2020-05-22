#pragma once
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "../../ext/GLFW/include/GLFW/glfw3.h"

namespace Mistiq
{
	class Input
	{
	public:
		Input() = default;
		~Input();

		bool KeyPressed(int a_Key);
		bool KeyReleased(int a_Key);

	private:
		GLFWwindow* m_Window = nullptr;

		void SetWindow(GLFWwindow* a_Window);

		friend class Application;
	};
}



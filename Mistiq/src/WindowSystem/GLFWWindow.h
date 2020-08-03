#pragma once
#include "Window.h"
#include "../Localization/Localization.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"

#include "../ECS/Components/Components.h"
#include "../ext/GLFW/include/GLFW/glfw3.h"
#include "EventSystem/Event.h"

namespace Mistiq {
	class ShaderProgram;
	class Texture;
	class Application;

	class GLFWWindow : public Window {
	public:
		GLFWWindow(std::shared_ptr<Application> a_Application);
		~GLFWWindow();

        void Create(WindowProperties a_WindowProperties, bool a_VSync = false) override;
        void Update(float a_DeltaTime) override;
        void Destroy() override;

        bool IsOpen() override;

		void CheckDelta(float m_DeltaTime);
		Event<void(float)> FloatEvent;

	public:
		GLFWwindow* m_Window;
		bool m_IsOpen;
		int m_FPS;

	private:
		Localization m_Localization;
		std::shared_ptr<Application> m_Application;

		std::shared_ptr<Mistiq::ShaderProgram> lighting;
		std::shared_ptr<Mistiq::ShaderProgram> lamp;
		unsigned int lightVAO;
		unsigned int VBO, cubeVAO;
		bool m_VSync;

		float m_DeltaTime;
		int m_FPSCounter;
	};
}

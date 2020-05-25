#pragma once
#include "Window.h"
#include "../Localization/Localization.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"

#include "../ECS/Components/MeshRenderer.h"
#include "../ext/GLFW/include/GLFW/glfw3.h"

namespace Mistiq {
	class ShaderProgram;
	class Texture;

	class GLFWWindow : public Window {
	public:
		GLFWWindow();
		~GLFWWindow();

        void Create(WindowProperties a_WindowProperties, bool a_VSync = false) override;
        void Update(float a_DeltaTime) override;
        void Destroy() override;

        bool IsOpen() override;

	public:
		GLFWwindow* m_Window;
		bool m_IsOpen;
		int m_FPS;

		std::vector<std::shared_ptr<MeshRenderer>> allModels;

	private:
		Localization m_Localization;

		std::shared_ptr<Mistiq::ShaderProgram> lighting;
		std::shared_ptr<Mistiq::ShaderProgram> lamp;
		unsigned int lightVAO;
		unsigned int VBO, cubeVAO;
		bool m_VSync;

		float m_DeltaTime;
		int m_FPSCounter;
	};
}

#pragma once
#include "Window.h"
#include "imgui_impl_glfw.h"
#include "../../ext/GLFW/include/GLFW/glfw3.h"
#include "../Localization/Localization.h"
#include "../../ext/glm/glm/glm.hpp"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"

namespace Mistiq {
	class ShaderProgram;
	class Texture;

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

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		std::shared_ptr<ShaderProgram> program;
		std::shared_ptr<Texture> texture1;

		std::vector<std::shared_ptr<ModelData>> model;
	};
}

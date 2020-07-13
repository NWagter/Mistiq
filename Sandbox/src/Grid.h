#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <fstream>
#include <sstream>

#include "../ext/tinygltf/tiny_gltf.h"

#include "../ext/Glad/include/glad/glad.h"

#include "../ext/glm/glm/glm.hpp"
#include "../ext/glm/glm/gtc/matrix_transform.hpp"
#include "../ext/glm/glm/gtc/type_ptr.hpp"

#include "../ext/GLFW/include/GLFW/glfw3.h"

#include "WindowSystem/imgui_impl_glfw.h"
#include "WindowSystem/imgui_impl_opengl3.h"

#include <ECS/Component.h>

class SandboxApp;

namespace Mistiq
{
	class Grid final : public Mistiq::Component
	{
	public:
		Grid(unsigned int a_Width, unsigned int a_Height, SandboxApp* app);
		~Grid();

		void Start() override;
		void Update(float a_DeltaTime) override;

	private:
		unsigned int m_Width;
		unsigned int m_Height;

		int m_GridLayout[169]{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
			0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0,
			0, 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 2,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0,
			2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
			0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0,
			0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0,
			0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0,
		};
	};
}

#pragma once
#include "ECS/Component.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"

#include "../../../ext/glad/include/glad/glad.h"

namespace Mistiq
{
    struct Mesh : public Component
    {
		static unsigned int s_Type;

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		std::shared_ptr<Mistiq::ShaderProgram> program;
		std::shared_ptr<Mistiq::Texture> texture1;
		std::shared_ptr<Mistiq::ModelData> model;

		bool enabled;

		glm::mat4 Model;
		glm::mat4 Model2;
    };

    struct Location : public Component
    {
		static unsigned int s_Type;

		glm::vec3 m_Translation;
		glm::vec4 m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_Model;
    };
}
#pragma once
#include "ECS/Component.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"

#include "../../../ext/glad/include/glad/glad.h"

namespace Mistiq
{
	class MeshRenderer : public Mistiq::Component
	{
	public:
		void Start() override;
		void Update(float a_DeltaTime) override;

	    unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		std::shared_ptr<Mistiq::ShaderProgram> program;
		std::shared_ptr<Mistiq::Texture> texture1;
		std::shared_ptr<Mistiq::ModelData> model;

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		friend class GLFWWindow;

	public:
		MeshRenderer(std::shared_ptr<Mistiq::ModelData> a_Model) {

			model = a_Model;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, model->primitives[0]->vertices.size() * sizeof(Mistiq::Vertex), &model->primitives[0]->vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->primitives[0]->indices.size() * sizeof(unsigned int), &model->primitives[0]->indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mistiq::Vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mistiq::Vertex), (void*)offsetof(Mistiq::Vertex, normal));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mistiq::Vertex), (void*)offsetof(Mistiq::Vertex, tex));


			program = std::make_shared<Mistiq::ShaderProgram>();
			std::shared_ptr<Mistiq::Shader> vertShader = std::make_shared<Mistiq::Shader>("assets/shaders/shader.vert", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_VERTEX);
			std::shared_ptr<Mistiq::Shader> fragShader = std::make_shared<Mistiq::Shader>("assets/shaders/shader.frag", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_FRAGMENT);

			program->AddShader(vertShader);
			program->AddShader(fragShader);
			program->Link();
			program->Use();

			texture1 = std::make_shared<Mistiq::Texture>("assets/models/Bitmaptexture-Bitmaptexture.png", true);
			texture1->Load();

			program->Use();
			program->SetInt("texture1", 0);
		}
	};
}
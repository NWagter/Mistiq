#pragma once
#include "ECS/System.h"
#include "ECS/Components/Components.h"

#include "Mistiq/Application.h"
#include "ECS/ECSManager.h"

#include <set>

namespace Mistiq
{
    class MeshRenderer : public System
    {
	public:
		MeshRenderer() {
			std::set<unsigned int> requiredComponents;
			requiredComponents.insert(Mistiq::Mesh::s_Type);
			requiredComponents.insert(Mistiq::Location::s_Type);
			m_RequiredComponents = requiredComponents;
		}

		void Update() override {
			std::cout << std::endl;
			for (auto entity : m_MatchingEntities) {
				std::shared_ptr<Mesh> mesh = Application::instance().m_ECSManager->GetComponent<Mesh>(entity);
				std::shared_ptr<Location> location = Application::instance().m_ECSManager->GetComponent<Location>(entity);

                if(!mesh->enabled)
                {
					mesh->enabled = true;

					glGenVertexArrays(1, &mesh->VAO);
					glGenBuffers(1, &mesh->VBO);
					glGenBuffers(1, &mesh->EBO);

					glBindVertexArray(mesh->VAO);
					glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
					glBufferData(GL_ARRAY_BUFFER, mesh->model->primitives[0]->vertices.size() * sizeof(Mistiq::Vertex), &mesh->model->primitives[0]->vertices[0], GL_STATIC_DRAW);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->model->primitives[0]->indices.size() * sizeof(unsigned int), &mesh->model->primitives[0]->indices[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mistiq::Vertex), (void*)0);

					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mistiq::Vertex), (void*)offsetof(Mistiq::Vertex, normal));

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mistiq::Vertex), (void*)offsetof(Mistiq::Vertex, tex));


					mesh->program = std::make_shared<Mistiq::ShaderProgram>();
					std::shared_ptr<Mistiq::Shader> vertShader = std::make_shared<Mistiq::Shader>("assets/shaders/basic_lighting.vert", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_VERTEX);
					std::shared_ptr<Mistiq::Shader> fragShader = std::make_shared<Mistiq::Shader>("assets/shaders/basic_lighting.frag", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_FRAGMENT);

					mesh->program->AddShader(vertShader);
					mesh->program->AddShader(fragShader);
					mesh->program->Link();
					mesh->program->Use();

					mesh->texture1 = std::make_shared<Mistiq::Texture>("assets/models/Environment/Blockout/BlockoutTemp.png");
					mesh->texture1->Load();

					mesh->program->Use();
					mesh->program->SetInt("texture1", 0);
                }

				mesh->Model = glm::mat4(1.0f);
				mesh->Model = glm::translate(mesh->Model, glm::vec3(location->m_Translation.x, location->m_Translation.y, location->m_Translation.z));
				mesh->Model = glm::rotate(mesh->Model, glm::radians(location->m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
				mesh->Model = glm::rotate(mesh->Model, glm::radians(location->m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
				mesh->Model = glm::rotate(mesh->Model, glm::radians(location->m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
				mesh->Model = glm::scale(mesh->Model, glm::vec3(location->m_Scale.x, location->m_Scale.y, location->m_Scale.z));
			}
		}
    };

	class Transform : public System
	{
	public:
		Transform() {
			std::set<unsigned int> requiredComponents;
			requiredComponents.insert(Mistiq::Location::s_Type);
			m_RequiredComponents = requiredComponents;
		}

		void Update() override {
			for (auto entity : m_MatchingEntities) {
				
			}
		}
	};
}
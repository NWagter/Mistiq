#pragma once
#include "ECS/System.h"
#include "Components.h"
#include <set>
#include "Mistiq/Application.h"
#include "Graphics/ModelLoading/ModelLoader.h"
#include "ECS/Systems/Systems.h"
#include "ECS/Components/Components.h"

class Grid : public Mistiq::System
{
public:
	Grid() {
		std::set<unsigned int> requiredComponents;
		requiredComponents.insert(GridComponent::s_Type);
		m_RequiredComponents = requiredComponents;
	}

	void Update() override {
		for (auto entity : m_MatchingEntities) {
			std::shared_ptr<GridComponent> grid = Mistiq::Application::instance().m_ECSManager->GetComponent<GridComponent>(entity);

			if (!grid->enabled)
			{
				grid->enabled = true;

				int scale = 39;
				grid->m_Width = 13;
				grid->m_Height = 13;

				int gridCount = 0;
				for (int x = 0; x < grid->m_Width; x++)
				{
					for (int y = grid->m_Height - 1; y >= 0; y--)
					{
						//Empty tile, don nothing
						if (grid->m_GridLayout[gridCount] == 0) {}
						//Block, spawn block 
						else if (grid->m_GridLayout[gridCount] == 1)
						{
							Mistiq::Entity go = Mistiq::ModelLoader::InstantiateOne("assets/models/Environment/Props/Haystack/Haystack.gltf");

							std::shared_ptr<Mistiq::Location> loc = Mistiq::Application::instance().m_ECSManager->GetComponent<Mistiq::Location>(go);
							loc->m_Translation = glm::vec3(-230.0f + x * scale, 0, -230.0f + y * scale);
							loc->m_Scale = glm::vec3(1, 1, 1);
						}
						//Destroyable, spawn destroyable
						else if (grid->m_GridLayout[gridCount] == 2)
						{
							Mistiq::Entity go = Mistiq::ModelLoader::InstantiateOne("assets/models/Environment/Props/Barrel/Barrel.gltf");

							std::shared_ptr<Mistiq::Location> loc = Mistiq::Application::instance().m_ECSManager->GetComponent<Mistiq::Location>(go);
							loc->m_Translation = glm::vec3(-230.0f + x * scale, 0, -230.0f + y * scale);
							loc->m_Scale = glm::vec3(1, 1, 1);
						}


						gridCount++;
					}
				}
			}
		}
	}
};
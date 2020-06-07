#include "Grid.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshRenderer.h"
#include "src/SandboxApp.h"

Mistiq::Grid::Grid(unsigned a_Width, unsigned a_Height, SandboxApp* app)
{
	std::vector<std::shared_ptr<Mistiq::ModelData>> haystack = Mistiq::GLTFParser::Load("assets/models/Environment/Props/Haystack/Haystack.gltf");
	std::vector<std::shared_ptr<Mistiq::ModelData>> barrel = Mistiq::GLTFParser::Load("assets/models/Environment/Props/Barrel/Barrel.gltf");

	int scale = 39;

	int gridCount = 0;
    for(int x = 0; x < a_Width; x++)
    {
        for(int y = a_Height - 1; y >= 0; y--)
        {
            //Empty tile, don nothing
            if(m_GridLayout[gridCount] == 0) {}
            //Block, spawn block 
			else if(m_GridLayout[gridCount] == 1)
			{
				for (int i = 0; i < haystack.size(); i++)
				{
					std::shared_ptr<Mistiq::GameObject> go = app->m_ECSManager->AddGameObject(haystack[i]->name);
					std::shared_ptr<Mistiq::Transform> transformComponent = std::make_shared<Mistiq::Transform>();
					go->AddComponent(transformComponent);

					transformComponent->SetTranslation(glm::vec3(-230.0f + x * scale, 0, -230.0f + y * scale));
					transformComponent->SetRotation(glm::vec4(90 + haystack[i]->node.rotation[0], haystack[i]->node.rotation[1], haystack[i]->node.rotation[2], 1.0f));
					transformComponent->SetScale(glm::vec3(haystack[i]->node.scale[0] * 100, haystack[i]->node.scale[1] * 100, haystack[i]->node.scale[2] * 100));

					std::shared_ptr<Mistiq::MeshRenderer> meshComponent = std::make_shared<Mistiq::MeshRenderer>(haystack[i]);
					go->AddComponent(meshComponent);
					app->m_Window->allModels.push_back(meshComponent);
				}
			}
            //Destroyable, spawn destroyable
			else if(m_GridLayout[gridCount] == 2)
			{
				for (int i = 0; i < barrel.size(); i++)
				{
					std::shared_ptr<Mistiq::GameObject> go = app->m_ECSManager->AddGameObject(barrel[i]->name);
					std::shared_ptr<Mistiq::Transform> transformComponent = std::make_shared<Mistiq::Transform>();
					go->AddComponent(transformComponent);

					transformComponent->SetTranslation(glm::vec3(-230.0f + x * scale, 0, -230.0f + y * scale));
					transformComponent->SetRotation(glm::vec4(90 + barrel[i]->node.rotation[0], barrel[i]->node.rotation[1], barrel[i]->node.rotation[2], 1.0f));
					transformComponent->SetScale(glm::vec3(barrel[i]->node.scale[0] * 100, barrel[i]->node.scale[1] * 100, barrel[i]->node.scale[2] * 100));

					std::shared_ptr<Mistiq::MeshRenderer> meshComponent = std::make_shared<Mistiq::MeshRenderer>(barrel[i]);
					go->AddComponent(meshComponent);
					app->m_Window->allModels.push_back(meshComponent);
				}
			}
			

			gridCount++;
        }
    }
}

Mistiq::Grid::~Grid()
{
}

void Mistiq::Grid::Start()
{
}

void Mistiq::Grid::Update(float a_DeltaTime)
{
}

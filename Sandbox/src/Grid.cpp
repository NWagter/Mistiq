#include "Grid.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshRenderer.h"
#include "SandboxApp.h"

#include "Graphics/ModelLoading/ModelLoader.h"

Mistiq::Grid::Grid(unsigned a_Width, unsigned a_Height, SandboxApp* app)
{
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
				std::shared_ptr<Mistiq::GameObject> go = ModelLoader::Instantiate("assets/models/Environment/Props/Haystack/Haystack.gltf");

				go->GetComponent<Transform>()->SetTranslation(glm::vec3(-230.0f + x * scale, 0, -230.0f + y * scale));
				go->GetComponent<Transform>()->SetRotation(glm::vec4(90 + 0, 0, 0, 1.0f));
				go->GetComponent<Transform>()->SetScale(glm::vec3(1, 1, 1));

				app->m_Window->allModels.push_back(go->GetComponent<MeshRenderer>());
			}
            //Destroyable, spawn destroyable
			else if(m_GridLayout[gridCount] == 2)
			{
				std::shared_ptr<Mistiq::GameObject> go = ModelLoader::Instantiate("assets/models/Environment/Props/Barrel/Barrel.gltf");

				go->GetComponent<Transform>()->SetTranslation(glm::vec3(-230.0f + x * scale, 0, -230.0f + y * scale));
				go->GetComponent<Transform>()->SetRotation(glm::vec4(90 + 0, 0, 0, 1.0f));
				go->GetComponent<Transform>()->SetScale(glm::vec3(1, 1, 1));

				app->m_Window->allModels.push_back(go->GetComponent<MeshRenderer>());
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

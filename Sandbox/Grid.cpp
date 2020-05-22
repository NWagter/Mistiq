#include "Grid.h"
#include "Graphics/ModelLoading/GLTF/GLTFParser.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshRenderer.h"
#include "src/SandboxApp.h"

Mistiq::Grid::Grid(unsigned a_Width, unsigned a_Height, SandboxApp* app)
{
	/*std::vector<std::shared_ptr<Mistiq::ModelData>> model = Mistiq::GLTFParser::Load("assets/models/Bomberman.gltf");

	int scale = 39;

    for(int x = 0; x < a_Width; x++)
    {
        for(int y = 0; y < a_Height; y++)
        {
			for (int i = 0; i < model.size(); i++)
			{
				std::shared_ptr<Mistiq::GameObject> go = app->m_ECSManager->AddGameObject(model[i]->name);
				std::shared_ptr<Mistiq::Transform> transformComponent = std::make_shared<Mistiq::Transform>();
				go->AddComponent(transformComponent);

				transformComponent->SetPosition(glm::vec3(-230.0f + x * scale, 50, -230.0f + y * scale));
				transformComponent->SetRotation(glm::vec4(model[i]->node.rotation[0], model[i]->node.rotation[1], model[i]->node.rotation[2], 1.0f));
				transformComponent->SetScale(glm::vec3(4, 4, 4));

				std::shared_ptr<Mistiq::MeshRenderer> meshComponent = std::make_shared<Mistiq::MeshRenderer>(model[i]);
				go->AddComponent(meshComponent);
				app->m_Window->allModels.push_back(meshComponent);
			}
        }
    }*/
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

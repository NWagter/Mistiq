#include "Mstqpch.h"
#include "ModelLoader.h"
#include "GLTF/GLTFParser.h"

#include "ECS/Components/MeshRenderer.h"
#include "ECS/Components/Transform.h"

std::shared_ptr<Mistiq::GameObject> Mistiq::ModelLoader::Instantiate(const char* a_PathToObject)
{
	return BaseInstantiate(a_PathToObject);
}

std::shared_ptr<Mistiq::GameObject> Mistiq::ModelLoader::Instantiate(const char* a_PathToObject, glm::vec3 a_Pos)
{
	std::shared_ptr<GameObject> go = BaseInstantiate(a_PathToObject);
	go->GetComponent<Transform>()->SetTranslation(a_Pos);
	return go;
}

std::shared_ptr<Mistiq::GameObject> Mistiq::ModelLoader::BaseInstantiate(const char* a_PathToObject)
{
    //Creation of gameobject and transform component
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	std::shared_ptr<Transform> transformComponent = std::make_shared<Mistiq::Transform>();

    //Load the actual model,
    //TODO: Implement the option to load multiple meshes instead of only one
	std::shared_ptr<ModelData> model = GLTFParser::Load(a_PathToObject)[0];
	std::shared_ptr<MeshRenderer> meshComponent = std::make_shared<MeshRenderer>(model);

    //Adding components
	go->AddComponent(transformComponent);
	go->AddComponent(meshComponent);

	return go;
}

#include "Mstqpch.h"
#include "ModelLoader.h"
#include "GLTF/GLTFParser.h"

#include "ECS/Components/MeshRenderer.h"
#include "ECS/Components/Transform.h"

std::shared_ptr<Mistiq::GameObject> Mistiq::ModelLoader::InstantiateOne(const char* a_PathToObject)
{
	return BaseInstantiate(a_PathToObject)[0];
}

std::shared_ptr<Mistiq::GameObject> Mistiq::ModelLoader::InstantiateOne(const char* a_PathToObject, glm::vec3 a_Pos)
{
	std::shared_ptr<GameObject> go = BaseInstantiate(a_PathToObject)[0];
	go->GetComponent<Transform>()->SetTranslation(a_Pos);
	return go;
}

std::vector<std::shared_ptr<Mistiq::GameObject>> Mistiq::ModelLoader::InstantiateMultiple(const char* a_PathToObject)
{
	return BaseInstantiate(a_PathToObject);
}

std::vector<std::shared_ptr<Mistiq::GameObject>> Mistiq::ModelLoader::BaseInstantiate(const char* a_PathToObject)
{
	//Load the actual model,
	std::vector<std::shared_ptr<ModelData>> models = GLTFParser::Load(a_PathToObject);

    //Creation of gameobject vector
	std::vector < std::shared_ptr<GameObject>> gameObjects;

    //For as many times as the models vector is big,
    //create GameObjects
    for(size_t i = 0; i < models.size(); ++i)
    {
		gameObjects.push_back(std::make_shared<GameObject>());

		std::shared_ptr<Transform> transformComponent = std::make_shared<Mistiq::Transform>();
		std::shared_ptr<MeshRenderer> meshComponent = std::make_shared<MeshRenderer>(models[i]);

        //Set base transform values to the loaded in model transform values
        //Translation
		transformComponent->SetTranslation(glm::vec3(meshComponent->model->node.translation[0], 
			meshComponent->model->node.translation[2] * -1, 
			meshComponent->model->node.translation[1]));
        //Rotation
        //TODO: Find out why the magic number 90 is needed for the x rotation
		transformComponent->SetRotation(glm::vec4(90 + meshComponent->model->node.rotation[0],
			meshComponent->model->node.rotation[1],
			meshComponent->model->node.rotation[2],
			1));

        //Scale
		transformComponent->SetScale(glm::vec3(meshComponent->model->node.scale[0],
			meshComponent->model->node.scale[1],
			meshComponent->model->node.scale[2]));

		//Adding components
		gameObjects[i]->AddComponent(transformComponent);
		gameObjects[i]->AddComponent(meshComponent);
    }

	return gameObjects;
}

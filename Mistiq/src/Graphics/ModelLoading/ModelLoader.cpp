#include "Mstqpch.h"
#include "ModelLoader.h"
#include "GLTF/GLTFParser.h"

#include "Mistiq/Application.h"
#include "ECS/Components/Components.h"

Mistiq::Entity Mistiq::ModelLoader::InstantiateOne(const char* a_PathToObject)
{
	std::vector<Mistiq::Entity>& ents = BaseInstantiate(a_PathToObject);
	return BaseInstantiate(a_PathToObject)[0];
}

Mistiq::Entity Mistiq::ModelLoader::InstantiateOne(const char* a_PathToObject, glm::vec3 a_Pos)
{
	Entity& entity = BaseInstantiate(a_PathToObject)[0];
	Application::instance().m_ECSManager->GetComponent<Location>(entity)->m_Translation = a_Pos;
	return entity;
}

std::vector<Mistiq::Entity> Mistiq::ModelLoader::InstantiateMultiple(const char* a_PathToObject)
{
	return BaseInstantiate(a_PathToObject);
}

std::vector<Mistiq::Entity> Mistiq::ModelLoader::BaseInstantiate(const char* a_PathToObject)
{
	//Load the actual model,
	std::vector<std::shared_ptr<ModelData>> models = GLTFParser::Load(a_PathToObject);

    //Creation of entities vector
	std::vector<Mistiq::Entity> entities;

    //For as many times as the models vector is big,
    //create GameObjects
    for(size_t i = 0; i < models.size(); ++i)
    {
		Entity& entity = Application::instance().m_ECSManager->AddEntity();
		entities.push_back(entity);

		std::shared_ptr<Location> locationComponent = std::make_shared<Location>();
		std::shared_ptr<Mesh> meshComponent = std::make_shared<Mesh>();
		std::shared_ptr<NameComponent> nameComponent = std::make_shared<NameComponent>();

		meshComponent->model = models[i];

        //Set specific game object values
		nameComponent->name = meshComponent->model->name;

        //Set Base transform values to the loaded in model transform values
        //Translation
		locationComponent->m_Translation = glm::vec3(meshComponent->model->node.translation[0],
			meshComponent->model->node.translation[2] * -1, 
			meshComponent->model->node.translation[1]);
        //Rotation
        //TODO: Find out why the magic number 90 is needed for the x rotation
		locationComponent->m_Rotation = glm::vec4(90 + meshComponent->model->node.rotation[0],
			meshComponent->model->node.rotation[1],
			meshComponent->model->node.rotation[2],
			1);

        //Scale
		locationComponent->m_Scale = glm::vec3(meshComponent->model->node.scale[0],
			meshComponent->model->node.scale[1],
			meshComponent->model->node.scale[2]);

		Application::instance().m_ECSManager->AddComponent<Location>(entity, locationComponent);
		Application::instance().m_ECSManager->AddComponent<Mesh>(entity, meshComponent);
		Application::instance().m_ECSManager->AddComponent<NameComponent>(entity, nameComponent);
    }

	return entities;
}

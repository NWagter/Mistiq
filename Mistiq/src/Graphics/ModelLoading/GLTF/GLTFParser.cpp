#include "Mstqpch.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "GLTFParser.h"

std::vector<std::shared_ptr<Mistiq::ModelData>> Mistiq::GLTFParser::Load(const char* a_PathToGLTFFile)
{
	//Hierarchy to return
	std::vector<std::shared_ptr<ModelData>> hierarchy;

	//Load in whole document
	tinygltf::TinyGLTF loader;
	tinygltf::Model doc;
	std::string err;
	std::string warn;

	//Detect if binary or ascii gltf file & handle loading
	const std::string binaryExt = ".glb";
	const std::string asciiExt = ".gltf";
	const std::string strPath = static_cast<std::string>(a_PathToGLTFFile);
	if (strPath.substr(strPath.length() - 4) == binaryExt)
	{
		loader.LoadBinaryFromFile(&doc, &err, &warn, a_PathToGLTFFile);
	}
	else if (strPath.substr(strPath.length() - 5) == asciiExt)
	{
		loader.LoadASCIIFromFile(&doc, &err, &warn, a_PathToGLTFFile);
	}

	//Get scene in order to search for the correct nodes in the document
	const tinygltf::Scene& scene = doc.scenes[0];

	//Load models
	for (size_t i = 0; i < doc.nodes.size(); ++i)
	{
		if (doc.nodes[i].mesh >= 0)
		{
			std::shared_ptr<ModelData> modelData = LoadMeshFromNode(doc, doc.nodes[i]);
			modelData->node = doc.nodes[i];

			if (modelData->node.translation.empty())
			{
				for (size_t j = 0; j < 3; j++)
				{
					modelData->node.translation.push_back(0.0f);
				}
			}

			if (modelData->node.rotation.empty())
			{
				for (size_t j = 0; j < 3; j++)
				{
					modelData->node.rotation.push_back(0.0f);
				}
			}

			if (modelData->node.scale.empty())
			{
				for (size_t j = 0; j < 3; j++)
				{
					modelData->node.scale.push_back(1.0f);
				}
			}

			hierarchy.push_back(modelData);
		}
	}

	return hierarchy;
}

std::shared_ptr<Mistiq::ModelData> Mistiq::GLTFParser::LoadMeshFromNode(tinygltf::Model a_Document, tinygltf::Node a_Node)
{
	const tinygltf::Node& node = a_Node;

	std::shared_ptr<ModelData> modelData = std::make_shared<ModelData>();
	modelData->name = node.name;

	if (node.mesh >= 0)
	{
		//Creation and assigning of mesh object
		modelData->properties = a_Document.meshes[node.mesh];

		for (int primitiveID = 0; primitiveID < modelData->properties.primitives.size(); primitiveID++)
		{
			//Local ref to primitive
			auto primitiveData = modelData->properties.primitives[primitiveID];
			std::shared_ptr<DrawObjectData> primitive = std::make_shared<DrawObjectData>();

			///Set index buffer
			primitive->indexBuffer = GetBufferData(a_Document, primitiveData.indices);

			bool loadPosition = false;
			bool loadNormal = false;
			bool loadTexture = false;
			for (auto const& attrib : primitiveData.attributes)
			{
				//Get the buffer of positions, normals and texcoords
				if (attrib.first == "POSITION")
				{
					loadPosition = true;
					primitive->positionBuffer = GetBufferData(a_Document, attrib.second);
				}
				else if (attrib.first == "NORMAL")
				{
					loadNormal = true;
					primitive->normalBuffer = GetBufferData(a_Document, attrib.second);;
				}
				else if (attrib.first == "TEXCOORD_0")
				{
					loadTexture = true;
					primitive->texCoordBuffer = GetBufferData(a_Document, attrib.second);;
				}
			}

			//Build all the vertices.
			for (std::uint32_t index = 0; index < primitive->positionBuffer.numberOfElements; ++index)
			{
				//Calculate the offsets into the buffers where the current stuff resides.
				const glm::vec3 position = *primitive->positionBuffer.GetElement<glm::vec3>(index);
				const glm::vec3 normal = *primitive->normalBuffer.GetElement<glm::vec3>(index);
				glm::vec2 texCoord = glm::vec2();

				if (loadTexture)
					texCoord = *primitive->texCoordBuffer.GetElement<glm::vec2>(index);

				//Put the new vertex in the vertices vector.
				primitive->vertices.emplace_back(Vertex(position, normal, texCoord));

			}

			//Insert all the indices in the index buffer.
			primitive->indices.reserve(primitive->indexBuffer.numberOfElements);
			for (std::uint32_t i = 0; i < primitive->indexBuffer.numberOfElements; ++i)
			{
				auto index = *primitive->indexBuffer.GetElement<uint16_t>(i);
				primitive->indices.emplace_back(index);
			}

			//Load material for primitive
			primitive->material = LoadMaterialFromPrimitive(a_Document, primitiveData);

			modelData->primitives.push_back(primitive);
		}
	}

	//Assign children
	for (size_t i = 0; i < node.children.size(); i++)
	{
		std::shared_ptr<ModelData> data = LoadMeshFromNode(a_Document, a_Document.nodes[node.children[i]]);
		modelData->children.push_back(data);
	}

	return modelData;
}

std::shared_ptr<Mistiq::MaterialData> Mistiq::GLTFParser::LoadMaterialFromPrimitive(::tinygltf::Model a_Document, ::tinygltf::Primitive a_Primitive)
{
	std::shared_ptr<MaterialData> drawObjectMaterial = std::make_shared<MaterialData>();

	if (a_Primitive.material >= 0)
	{
		tinygltf::Material& matProperties = a_Document.materials[a_Primitive.material];

		//Setting base color
		drawObjectMaterial->baseColor = glm::vec4(
			matProperties.pbrMetallicRoughness.baseColorFactor[0],
			matProperties.pbrMetallicRoughness.baseColorFactor[1],
			matProperties.pbrMetallicRoughness.baseColorFactor[2],
			matProperties.pbrMetallicRoughness.baseColorFactor[3]
		);
		//metal factor
		drawObjectMaterial->metalFactor = matProperties.pbrMetallicRoughness.metallicFactor;
		//Roughness factor
		drawObjectMaterial->roughnessFactor = matProperties.pbrMetallicRoughness.roughnessFactor;
		//Normal texture
		if (a_Document.materials[a_Primitive.material].normalTexture.index >= 0)
		{
			tinygltf::Texture& texture = a_Document.textures[a_Document.materials[a_Primitive.material].normalTexture.index];

			if (texture.source >= 0)
			{
				drawObjectMaterial->normalTextureImage = a_Document.images[texture.source];
			}
		}
		//Occlusion texture
		if (a_Document.materials[a_Primitive.material].occlusionTexture.index >= 0)
		{
			tinygltf::Texture& texture = a_Document.textures[a_Document.materials[a_Primitive.material].occlusionTexture.index];

			if (texture.source >= 0)
			{
				drawObjectMaterial->occlusionTexturImage = a_Document.images[texture.source];
			}
		}
		//Base color texture
		if (a_Document.materials[a_Primitive.material].pbrMetallicRoughness.baseColorTexture.index >= 0)
		{
			tinygltf::Texture& texture = a_Document.textures[a_Document.materials[a_Primitive.material].pbrMetallicRoughness.baseColorTexture.index];

			if (texture.source >= 0)
			{
				drawObjectMaterial->baseColorTextureImage = a_Document.images[texture.source];
			}
		}
		//Metallic roughness texture
		if (a_Document.materials[a_Primitive.material].pbrMetallicRoughness.metallicRoughnessTexture.index >= 0)
		{
			tinygltf::Texture& texture = a_Document.textures[a_Document.materials[a_Primitive.material].pbrMetallicRoughness.metallicRoughnessTexture.index];

			if (texture.source >= 0)
			{
				drawObjectMaterial->metallicRoughnessTextureImage = a_Document.images[texture.source];
			}
		}
		//Emissive texture
		if (a_Document.materials[a_Primitive.material].emissiveTexture.index >= 0)
		{
			tinygltf::Texture& texture = a_Document.textures[a_Document.materials[a_Primitive.material].emissiveTexture.index];

			if (texture.source >= 0)
			{
				drawObjectMaterial->emissiveTextureImage = a_Document.images[texture.source];
			}
		}
	}

	return drawObjectMaterial;
}

Mistiq::BufferData Mistiq::GLTFParser::GetBufferData(::tinygltf::Model& a_Model, std::uint32_t a_AttributeIndex)
{
	//Accessor
	tinygltf::Accessor& accessor = a_Model.accessors[a_AttributeIndex];
	//Buffer view
	tinygltf::BufferView& bufferView = a_Model.bufferViews[accessor.bufferView];
	//Buffer
	tinygltf::Buffer& buffer = a_Model.buffers[bufferView.buffer];
	//Size of a single element in the accessor
	size_t dataTypeSize = DataTypeSize(accessor);
	//Calculate if there is any empty space
	size_t emptySpace = bufferView.byteStride == 0 ? 0 : bufferView.byteStride - dataTypeSize;

	//Return constructed object
	return BufferData(&accessor, &buffer.data[static_cast<uint64_t>(bufferView.byteOffset) + accessor.byteOffset], dataTypeSize, emptySpace, accessor.count);
}

size_t Mistiq::GLTFParser::DataTypeSize(::tinygltf::Accessor a_Accessor)
{
	uint32_t elementSize = 0;

	//Get single element data type size
	switch (a_Accessor.componentType)
	{
	case TINYGLTF_COMPONENT_TYPE_BYTE:
	case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
		elementSize = 1;
		break;
	case TINYGLTF_COMPONENT_TYPE_SHORT:
	case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
		elementSize = 2;
		break;
	case TINYGLTF_COMPONENT_TYPE_FLOAT:
	case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
		elementSize = 4;
		break;
	}

	//Based on what the data is representing,
	//multiply
	switch (a_Accessor.type)
	{
	case TINYGLTF_TYPE_MAT2:
		return 4 * elementSize;
		break;
	case TINYGLTF_TYPE_MAT3:
		return 9 * elementSize;
		break;
	case TINYGLTF_TYPE_MAT4:
		return 16 * elementSize;
		break;
	case TINYGLTF_TYPE_SCALAR:
		return elementSize;
		break;
	case TINYGLTF_TYPE_VEC2:
		return 2 * elementSize;
		break;
	case TINYGLTF_TYPE_VEC3:
		return 3 * elementSize;
		break;
	case TINYGLTF_TYPE_VEC4:
		return 4 * elementSize;
		break;
	}

	return 0;
}
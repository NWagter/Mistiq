#pragma once

#include "../../ext/tinygltf/tiny_gltf.h"
#include "../../ext/glm/glm/glm.hpp"
#include <memory>

namespace Mistiq
{
	//Struct containing information about a buffer
	struct BufferData
	{
		BufferData() : accessor(nullptr), data(nullptr), dataSize(0), totalSize(0), emptySpace(0), numberOfElements(0) {}

		BufferData(tinygltf::Accessor* a_Accessor, uint8_t const* a_Data, size_t a_DataSize, size_t a_EmptySpace, size_t a_NumberOfElements) :
			accessor(a_Accessor),
			data(a_Data),
			dataSize(a_DataSize),
			emptySpace(a_EmptySpace),
			numberOfElements(a_NumberOfElements)
		{
			//Calculate total size
			totalSize = static_cast<uint32_t>(a_Accessor->count) * a_DataSize;
		}

		//Pointer to accessor
		tinygltf::Accessor* accessor;

		//Start of the data
		uint8_t const* data;

		//The size of each data element in bytes
		size_t dataSize;

		//The total size of all elements together in bytes
		size_t totalSize;

		//Empty space between objects. Measured from the end of one object to the start of the next
		size_t emptySpace;

		//The amount of elements
		size_t numberOfElements;

		bool HasData() const noexcept
		{
			return data != nullptr;
		}

		//Struct containing information about a buffer
		template<typename T>
		T const* GetElement(uint32_t index)
		{
			//Make sure there is data, and that this type is the correct type
			//Also check for out of bounds
			assert(HasData() && "Error! No data in this BufferData object.");
			assert(sizeof(T) == dataSize && "Error! Data type specified is not of the same length as the internal format.");
			assert(index < numberOfElements && "Error! Index out of bounds for BufferData.");

			//Calculate the position of the object required and return it
			return reinterpret_cast<T const*>(reinterpret_cast<size_t>(data) + (static_cast<size_t>(index) * static_cast<size_t>(emptySpace)) + (static_cast<size_t>(index) * static_cast<size_t>(dataSize)));
		};
	};

	//Struct containing information about a Material
	struct MaterialData
	{
		//Base color of material
		glm::vec4 baseColor;
		//Metalic factor
		double metalFactor;
		//Roughness factor
		double roughnessFactor;

		//Properties
		tinygltf::Material properties;

		///All possible textures as images
		tinygltf::Image normalTextureImage;
		tinygltf::Image occlusionTexturImage;
		tinygltf::Image baseColorTextureImage;
		tinygltf::Image metallicRoughnessTextureImage;
		tinygltf::Image emissiveTextureImage;
	};

	//Temporary Vertext struct
	struct Vertex
	{
		Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 tex) : pos(pos), normal(normal), tex(tex) {}
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 tex;

	};

	//Struct containing information about a primitive
	struct DrawObjectData
	{
		//Index of this node
		std::uint16_t nodeIndex;

		//Parsed vertices from position, normal and texCoord buffers
		std::vector<Vertex> vertices;

		//Indices
		std::vector<unsigned int> indices;

		std::shared_ptr<MaterialData> material;

		//All buffers
		BufferData indexBuffer;
		BufferData positionBuffer;
		BufferData normalBuffer;
		BufferData texCoordBuffer;
	};

	struct ModelData
	{
		//Name of model
		std::string name;
		//Node of model
		tinygltf::Node node;
		//Properties of mesh in model
		tinygltf::Mesh properties;
		//Vector of primitives of the model
		std::vector<std::shared_ptr<DrawObjectData>> primitives;
		//Vector of all children models of this model
		std::vector<std::shared_ptr<ModelData>> children;
		//Material containing all textures of this model
		//std::shared_ptr<MaterialData> material;
	};

	class GLTFParser
	{
	public:
		static std::vector<std::shared_ptr<ModelData>> Load(const char* a_PathToGLTFFile);

	private:
		static std::shared_ptr<ModelData> LoadMeshFromNode(tinygltf::Model a_Document, tinygltf::Node a_Node);
		static std::shared_ptr<MaterialData> LoadMaterialFromPrimitive(tinygltf::Model a_Document, tinygltf::Primitive a_Primitive);
		static BufferData GetBufferData(tinygltf::Model& a_Model, std::uint32_t a_AttributeIndex);
		static size_t DataTypeSize(tinygltf::Accessor a_Accessor);
	};
}
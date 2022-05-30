#include "stdafx.h"
#include "ModelLoader.h"
#include "Fundation/Model/Model.h"
#include "ModelLoaderUtils.h"

ModelLoaderAssimp::ModelLoaderAssimp(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
	{
		CORE_ERROR("Fail to load model");
		return;
	}

	Self::processNode(scene->mRootNode, scene);
}

void ModelLoaderAssimp::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Ref<Mesh> aMesh = Self::processMesh(mesh, scene);
		_meshes.push_back(std::move(aMesh));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		Self::processNode(node->mChildren[i], scene);
	}
}


Ref<Mesh> ModelLoaderAssimp::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// Get vertices
	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D* vertice = mesh->mVertices;
		Vertex vertex;

		vertex._position.x = vertice[i].x;
		vertex._position.y = vertice[i].y;
		vertex._position.z = vertice[i].z;

		if (mesh->HasNormals())
		{
			aiVector3D* normal = mesh->mNormals;
			vertex._normal.x = normal[i].x;
			vertex._normal.y = normal[i].y;
			vertex._normal.z = normal[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex._texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex._texCoords.y = mesh->mTextureCoords[0][i].y;

			vertex._tangent.x = mesh->mTangents[i].x;
			vertex._tangent.y = mesh->mTangents[i].y;
			vertex._tangent.z = mesh->mTangents[i].z;

			vertex._bitangent.x = mesh->mBitangents[i].x;
			vertex._bitangent.y = mesh->mBitangents[i].y;
			vertex._bitangent.z = mesh->mBitangents[i].z;

		}
		else
		{
			vertex._texCoords = glm::vec2(0.f, 0.f);
		}

		vertices.push_back(std::move(vertex));
	}

	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	Ref<Material> mat = std::make_shared<Material>();

	aiColor4D color4;
	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color4))
	{
		mat->_diffuseColor = ASS_TO_GLM(color4);
	}

	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color4))
	{
		mat->_ambientColor = ASS_TO_GLM(color4);
	}

	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color4))
	{
		mat->_specularColor = ASS_TO_GLM(color4);
	}

	float value;
	if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &value))
	{
		mat->_glossiness = value;
	}

	if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS_STRENGTH, &value))
	{
		mat->_specularLevel = value;
	}

	return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(mat));
}

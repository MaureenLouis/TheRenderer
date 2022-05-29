#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"
#include "Renderer/Material/Material.h"
#include "Fundation/IO/ModelLoader.h"

Model::Model(const char* path)
{

	Unique<ModelLoader> loader = std::make_unique<ModelLoaderAssimp>(path);
	_meshes = std::move(loader->meshes());

}

void Model::draw(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p)
{
	for (auto mesh : _meshes)
	{
		mesh->draw(m, v, p);
	}
}

void Model::addMesh(Ref<Mesh>&& mesh)
{
	_meshes.push_back(std::move(mesh));
}


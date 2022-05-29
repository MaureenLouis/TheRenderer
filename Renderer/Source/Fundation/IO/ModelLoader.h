#pragma once
#include "Fundation/Model/Mesh.h"

FORWARD_DECL(Model);

class ModelLoader
{
public:
	virtual std::vector<Ref<Mesh>> meshes() = 0;
};

class ModelLoaderAssimp : public ModelLoader
{
	SELF(ModelLoaderAssimp);
	SUPER(ModelLoader);

public:
	ModelLoaderAssimp(const char* path);
	void processNode(aiNode* node, const aiScene* scene);
	Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	virtual std::vector<Ref<Mesh>> meshes()override { return _meshes; } ;

private:
	std::vector<Ref<Mesh>>  _meshes;

};


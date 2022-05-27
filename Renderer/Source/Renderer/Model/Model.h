#pragma once
#include "Mesh.h"

class Model 
{
	SELF(Model);
public:
	Model(const char* path);

	void draw() {};

private:
	void processNode(aiNode* node, const aiScene* scene);
	Ref<Mesh> processMesh(aiMesh* node, const aiScene* scene);

private:
	std::vector<Ref<Mesh>> _meshes;
};


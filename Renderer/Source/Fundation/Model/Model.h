#pragma once
#include "Mesh.h"

class Model 
{
	SELF(Model);
public:
	Model(const char* path);

	void draw(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p);
	void addMesh(Ref<Mesh>&& mesh);


	std::vector<Ref<Mesh>> _meshes;
};


#pragma once
#include "Vertex.h"


struct Mesh
{
	std::vector<Vertex>       _vertices;
	std::vector<unsigned int> _indices;
	


	Mesh(const std::vector<Vertex>&& vertices, const std::vector<unsigned int>&& indices);

	void draw()
	{

	}
};
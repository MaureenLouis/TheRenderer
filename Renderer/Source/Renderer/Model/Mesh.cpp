#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>&& vertices, const std::vector<unsigned int>&& indices)
{
	_vertices = std::move(vertices);
	_indices = std::move(indices);
}
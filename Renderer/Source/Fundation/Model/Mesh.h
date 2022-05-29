#pragma once
#include "Vertex.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Material/Material.h"

struct Mesh
{
	std::vector<Vertex>       _vertices;
	std::vector<unsigned int> _indices;
	Ref<Material>             _material;
	Unique<ShaderProgram> _program;
	Unique<VertexArray>   _vertexArray;
	Ref<VertexBuffer>  _vertexBuffer;
	Ref<IndexBuffer>   _indexBuffer;

	static const char* _vertexShaderSource;
    static const char* _fragmentShaderSource;

	Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, Ref<Material>& material);

	void draw(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p);
};
#include "stdafx.h"
#include "Mesh.h"
#include "Renderer/Material/Material.h"

const char* Mesh::_vertexShaderSource =R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoords;
layout(location=3) in vec3 aTangent;
layout(location=4) in vec3 aBiTangent;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main()
{    
    gl_Position = p * v * m * vec4(aPos, 1.0);
}
)";

const char* Mesh::_fragmentShaderSource = R"(
#version 330 core
layout(location=0) out vec4 outColor;
uniform vec4 diffuseColor;
uniform vec3 lightColor;
void main()
{
    outColor = diffuseColor;
}
)";

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, Ref<Material>& material)
{
	_vertices = std::move(vertices);
	_indices = std::move(indices);
	_material = std::move(material);

	BufferLayout layout =
	{
		{ BufferElement::BufferElementType::Float3, "aPos" },
		{ BufferElement::BufferElementType::Float3, "aNormal"},
		{ BufferElement::BufferElementType::Float2, "aTexCoords"},
	    { BufferElement::BufferElementType::Float3, "aTangent"},
		{ BufferElement::BufferElementType::Float3, "aBiTangent"}
	};

	_vertexArray = std::make_unique<VertexArray>();
	_vertexArray->bind();

	_vertexBuffer = std::make_shared<VertexBuffer>((float*)&_vertices[0], sizeof(Vertex) * _vertices.size());
	_vertexBuffer->setLayout(layout);
	_vertexArray->addVertexBuffer(_vertexBuffer);

	_indexBuffer = std::make_shared<IndexBuffer>((int*)&_indices[0],  _indices.size());
	_vertexArray->setIndexBuffer(_indexBuffer);

	_program = std::make_unique<ShaderProgram>(_vertexShaderSource, _fragmentShaderSource);
}

void Mesh::draw(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p)
{
	glm::vec4 diffuseColor = _material->materialColor(Material::Type::DiffuseColor);

	_program->use();
	_program->setUniform("m", m);
	_program->setUniform("v", v);
	_program->setUniform("p", p);
	_program->setUniform("diffuseColor", diffuseColor);

	_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, _indexBuffer->count(), GL_UNSIGNED_INT, 0);
}

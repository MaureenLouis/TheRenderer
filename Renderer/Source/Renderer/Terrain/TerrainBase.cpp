#include "stdafx.h"
#include "TerrainBase.h"

const char* TerrainBase::_vertexShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 mvp;
void main()
{
   gl_Position =  mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* TerrainBase::_fragmentShader = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 debugGridColor;
void main()
{
   FragColor = debugGridColor;
}
)";

TerrainBase::TerrainBase(unsigned int width, unsigned int height, Ref<TrackBall>& trackBall)
{
	_trackBall = trackBall;
	_width = width;
	_height = height;
}

void TerrainBase::initialize()
{
	// Generate a grid
	for (int j = 0; j <= _width; ++j)
	{
		for (int i = 0; i <= _height; ++i)
		{
			float x = (float)i ;
			float z = (float)j ;
			float y = 0.f;
			_gridVertices.push_back(glm::vec3(x, y, z));
		}
	}

	for (int j = 0; j < _width; ++j)
	{
		for (int i = 0; i < _height; ++i)
		{
			int row1 = j * (_width + 1);
			int row2 = (j + 1) * (_width + 1);

			// triangle 1
			_gridIndices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i + 1));

			// triangle 2
			_gridIndices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
		}
	}

	// Buffer
	BufferLayout layout =
	{
		{ BufferElement::BufferElementType::Float3, "aPos" },
	};
	_array = std::make_unique<VertexArray>();
	_array->bind();

	_vertices = std::make_shared<VertexBuffer>((float *)(_gridVertices.data()), sizeof(glm::vec3) * _gridVertices.size());
	_vertices->setLayout(layout);
	_array->addVertexBuffer(_vertices);

	_indices = std::make_shared<IndexBuffer>((int *)(_gridIndices.data()), _gridIndices.size() * 3);
	_array->setIndexBuffer(_indices);

    // Shader
	_shader = std::make_shared<ShaderProgram>(_vertexShader, _fragmentShader);
}

void TerrainBase::draw()
{
	glm::mat4& m = _trackBall->model();
	glm::mat4& p = _trackBall->project();
	glm::mat4& v = _trackBall->viewMatrix();

	_shader->use();
	_shader->setUniform("mvp", p * v * m);
	_shader->setUniform("debugGridColor", glm::vec4(0.5f, 0.5f, 0.5f, 0.5f));

	_array->bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, _indices->count(), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

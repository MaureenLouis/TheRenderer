#include "stdafx.h"
#include "2dObject.h"

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 mvp;
out vec2 TexCoord;
void main()
{
   gl_Position =  mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   TexCoord = aTexCoord;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
uniform vec4 color;
uniform sampler2D albedo;
out vec4 FragColor;
in vec2 TexCoord;
void main()
{
   FragColor =  texture(albedo, TexCoord);
}
)";


float vertices[] = {
		 2.5f, 0.0f,  2.5f,  1.f, 1.f,
		 2.5f, 0.0f, -2.5f,  1.f, 0.f,
		-2.5f, 0.0f, -2.5f,  0.f, 0.f,
		-2.5f, 0.0f,  2.5f,  0.f, 1.f
};

int indices[] = {
	0, 1, 3,
	1, 2, 3
};

Object2D::Object2D()
{
	BufferLayout layout = 
	{ 
		{ BufferElement::BufferElementType::Float3, "aPos" },
		{ BufferElement::BufferElementType::Float2, "aTexCoord" }
	};

	_vertexArray = std::make_unique<VertexArray>();
	_vertexArray->bind();

	_vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	_vertexBuffer->setLayout(layout);
	_vertexArray->addVertexBuffer(_vertexBuffer);

	_indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));
	_vertexArray->setIndexBuffer(_indexBuffer);

	_program = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
	_program->setUniform("color", glm::vec4(250, 250, 0, 255));
	_program->setUniform("mvp", glm::mat4(1.f));

	_texture = std::make_unique<Texture2D>("D:\\Projects\\TheRenderer\\Asset\\Texture\\wall.jpg");

}

void Object2D::draw()
{
	glActiveTexture(GL_TEXTURE0);
	_texture->bind();

	_program->use();
	_program->setUniform("albedo", 0);

	_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, _indexBuffer->count(), GL_UNSIGNED_INT, 0);

}

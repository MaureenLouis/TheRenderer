#include "stdafx.h"
#include "ScreenObject.h"

float ScreenObject::_vertices[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
};

int ScreenObject::_indices[] = {
	0, 1, 3,
	1, 2, 3
};

ScreenObject::ScreenObject()
{

}

ScreenObject::~ScreenObject()
{

}

void ScreenObject::initialize()
{
	BufferLayout layout =
	{
		{ BufferElement::BufferElementType::Float2, "aPos" },
		{ BufferElement::BufferElementType::Float2, "aTexCoord" }
	};

	_vertexArray = std::make_unique<VertexArray>();
	_vertexArray->bind();

	_vertexBuffer = std::make_shared<VertexBuffer>(_vertices, 24 * sizeof(float));
	_vertexBuffer->setLayout(layout);
	_vertexArray->addVertexBuffer(_vertexBuffer);


	const std::string& assetDir = Application::assetDir();
	std::string shaderProgramPath = assetDir + "\\Shader\\InherientShader\\ScreenShader.fx";
	_program = std::make_unique<ShaderProgram>(shaderProgramPath.c_str());
}

void ScreenObject::draw()
{
	glDisable(GL_DEPTH_TEST);
	// Draw screen rectangle
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);


	_program->use();
	glActiveTexture(GL_TEXTURE0);
	_program->setUniform("screenTexture", 1);

	_vertexArray->bind();
}

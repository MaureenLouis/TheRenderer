#include "stdafx.h"
#include "AxisObject.h"

const char* axisVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 mvp;
uniform mat4 scale;
void main()
{
   gl_Position = mvp * scale * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* axisFragmentShaderSource = R"(
#version 330 core
uniform vec4 axisColor;
out vec4 FragColor;
void main()
{
   FragColor = axisColor;
}
)";

AxisObject::AxisObject(AxisType axisType)
	: _axisType(axisType)
{
	// Data
	switch (_axisType.value())
	{
	case AxisType::xAxis:
	{
		_axisColor = glm::vec4(255, 0, 0, 255);
		_vertex[0] = glm::vec3(10.f, 0.f, 0.f);
		_vertex[1] = glm::vec3(-10.f, 0.f, 0.f);
		break;
	}
	case AxisType::yAxis:
	{
		_axisColor = glm::vec4(0, 255, 0,255);
		_vertex[0] = glm::vec3(0.f, 0.f, 10.f);
		_vertex[1] = glm::vec3(0.f, 0.f, -10.f);
		break;
	}
	case AxisType::zAxis:
	{
		_axisColor = glm::vec4(0, 0, 255, 255);
		_vertex[0] = glm::vec3(0.f, 10.f, 0.f);
		_vertex[1] = glm::vec3(0.f, -10.f, 0.f);
		break;
	}
	}

	// Index
	_index = { 0u, 1u };


	// Buffers
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertex.size() * sizeof(glm::vec3), glm::value_ptr(_vertex[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _index.size() * sizeof(unsigned int), _index.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Shaders
	_program = std::make_unique<ShaderProgram>(axisVertexShaderSource, axisFragmentShaderSource);
	_program->setUniform("axisColor",_axisColor);
	_program->setUniform("scale", _scaledMatrix);
}

AxisObject::~AxisObject()
{
	glDeleteBuffers(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

void AxisObject::setAntialiasing(bool enable)
{
	_antialiasing = enable;
	if (_antialiasing)
	{
	    glEnable(GL_LINE_SMOOTH);
	}
	else
	{
		glDisable(GL_LINE_SMOOTH);
	}
}

void AxisObject::setLineWidth(float width)
{
	glLineWidth(width);
}

void AxisObject::setScaled(float scaled)
{
	_scaled = scaled;
	_scaledMatrix = glm::scale(_scaledMatrix, glm::vec3(_scaled, _scaled, _scaled));
	_program->setUniform("scale", _scaledMatrix);
}

void AxisObject::draw()
{
	_program->use();

	glBindVertexArray(_VAO);
	glDrawElements(GL_LINES, (GLsizei)_index.size(), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

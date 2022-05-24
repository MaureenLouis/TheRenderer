#include "stdafx.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_handler);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &_handler);
}

void VertexArray::bind() const
{
	glBindVertexArray(_handler);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{

	uint32_t index = 0;
	const auto& layout = vertexBuffer->layout();

	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.componentCount(),
			GL_FLOAT,
			element.isNormalized(),
			layout.stride(),
			(const void*)element._offset);
		index++;
	}

	_vertexBuffer.push_back(vertexBuffer);
}

void VertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	_indexBuffer = indexBuffer;
}

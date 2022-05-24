#pragma once
#include "stdafx.h"
#include "Buffer.h"

GLenum BufferElement::openGLDataType() const
{
	GLenum glType = GL_INVALID_ENUM;

	switch (_type.value())
	{
	case BufferElementType::Float:  glType = GL_FLOAT;     break;
	case BufferElementType::Float2: glType = GL_FLOAT;     break;
	case BufferElementType::Float3: glType = GL_FLOAT;     break;
	case BufferElementType::Float4: glType = GL_FLOAT;	    break;
	case BufferElementType::Mat3:   glType = GL_FLOAT;     break;
	case BufferElementType::Mat4:   glType = GL_FLOAT;     break;
	case BufferElementType::Int:    glType = GL_INT;		break;
	case BufferElementType::Int2:   glType = GL_INT;	    break;
	case BufferElementType::Int3:   glType = GL_INT;	    break;
	case BufferElementType::Int4:   glType = GL_INT;	    break;
	case BufferElementType::Bool:   glType = GL_BOOL;	    break;
	default: assert(false);
	}

	return glType;
}


size_t BufferElement::bufferElementSize(BufferElement::BufferElementType t)
{
	size_t size = 0;
	switch (t.value())
	{
	case BufferElementType::Float:  size = 1 * sizeof(float); break;
	case BufferElementType::Float2: size = 2 * sizeof(float); break;
	case BufferElementType::Float3: size = 3 * sizeof(float); break;
	case BufferElementType::Float4: size = 4 * sizeof(float); break;
	case BufferElementType::Mat3:   size = 4 * 3 * 3; break;
	case BufferElementType::Mat4:   size = 4 * 4 * 4; break;
	case BufferElementType::Int:    size = 4;		   break;
	case BufferElementType::Int2:   size = 4 * 2;	   break;
	case BufferElementType::Int3:   size = 4 * 3;	   break;
	case BufferElementType::Int4:   size = 4 * 4;	   break;
	case BufferElementType::Bool:   size = 4 * 4;	   break;
	default: assert(false); break;
	}

	return size;
}

size_t BufferElement::componentCount() const
{
	size_t size = 0;

	switch (_type.value())
	{
	case BufferElementType::Float:  size = 1;         break;
	case BufferElementType::Float2: size = 2;         break;
	case BufferElementType::Float3: size = 3;         break;
	case BufferElementType::Float4: size = 4;	       break;
	case BufferElementType::Mat3:   size = 3 * 3;     break;
	case BufferElementType::Mat4:   size = 4 * 4;     break;
	case BufferElementType::Int:    size = 1;		   break;
	case BufferElementType::Int2:   size = 2;	       break;
	case BufferElementType::Int3:   size = 3;	       break;
	case BufferElementType::Int4:   size = 4;	       break;
	case BufferElementType::Bool:   size = 1;	       break;
	default: assert(false);
	}

	return size;
}



VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
	glGenBuffers(1, &_vertexBufferHandler);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferHandler);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBufferHandler);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferHandler);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


IndexBuffer::IndexBuffer(int* indices, uint32_t count)
	:_count(count)
{
	glGenBuffers(1, &_indexBufferHandler);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandler);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_indexBufferHandler);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandler);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

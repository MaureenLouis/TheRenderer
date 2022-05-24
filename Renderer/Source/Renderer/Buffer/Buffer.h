#pragma once
#include "Fundation/Type/Enumerate.h"



class BufferElement
{
public:
	Enumerate(BufferElementType, uint8_t,
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool);

	BufferElement(BufferElementType bufferElementType, const char* name, bool normalize = false)
		: _type(bufferElementType),
		_name(name),
		_normalized(normalize),
		_size(bufferElementSize(bufferElementType)),
		_offset(0)
	{

	}

	size_t componentCount() const;

	GLboolean isNormalized() const { return _normalized ? GL_TRUE : GL_FALSE; }

	GLenum openGLDataType() const;

private:
	static size_t bufferElementSize(BufferElement::BufferElementType t);

public:
	BufferElementType _type;
	const char*       _name;
	bool              _normalized;
	unsigned int      _offset;
	size_t            _size;

};

class BufferLayout
{
public:
	BufferLayout() = default;
	BufferLayout(const std::initializer_list<BufferElement>& element)
		: _elements(element)
	{
		uint32_t offset = 0;
		_stride = 0;

		for (auto& element : _elements)
		{
			element._offset = offset;
			offset += element._size;
			_stride += element._size;


		}
	}

	uint32_t stride() const { return _stride; }

	std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
	std::vector<BufferElement>::iterator end() { return _elements.end(); }
	std::vector<BufferElement>::const_iterator begin()  const { return _elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }

private:
	std::vector<BufferElement> _elements;
	uint32_t                   _stride;
};

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, uint32_t size);
	virtual ~VertexBuffer();

	void bind() const;
	void unbind() const;

	void setLayout(BufferLayout& layout) { _layout = layout; }
	const BufferLayout& layout() const { return _layout; }

private:
	BufferLayout _layout;
	unsigned int _vertexBufferHandler;
};

class IndexBuffer
{
public:
	IndexBuffer(int* indices, uint32_t count);
	virtual ~IndexBuffer();

	void bind() const;
	void unbind() const;

	uint32_t count() const { return _count; }

private:
	unsigned int _indexBufferHandler;
	uint32_t _count;

};
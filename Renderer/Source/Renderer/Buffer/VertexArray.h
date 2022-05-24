#pragma once
#include "Fundation/Ref/Ref.h"
#include "Buffer.h"

class VertexArray
{
	SELF(VertexArray);
public:
	VertexArray();
	virtual ~VertexArray();

	void bind() const;
	void unbind() const;

	void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
	void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

	unsigned int handler() const { return _handler; }

private:
	unsigned int _handler;

	Ref<IndexBuffer> _indexBuffer;
	std::vector<Ref<VertexBuffer>> _vertexBuffer;
};
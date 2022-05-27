#pragma once
#include "RenderObject.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexArray.h"

class GridObject : public RenderObject
{
public:
	GridObject();

	virtual void draw() override;

	virtual Unique<ShaderProgram>& shader() override
	{
		return _program;
	}

private:
	Unique<ShaderProgram> _program;
	Unique<VertexArray>   _vertexArray;
	Ref<VertexBuffer>  _vertexBuffer;
	Ref<IndexBuffer>   _indexBuffer;

	static const char* _vertexShaderSource;
	static const char* _fragmentShaderSource;
};

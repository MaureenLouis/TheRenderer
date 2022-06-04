#pragma once
#include "RenderObject.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderProgram.h"

class ScreenObject : public RenderObject
{
public:
	ScreenObject();
	~ScreenObject();

	virtual void initialize() override;
	virtual void draw() override;

public:
	static float _vertices[24];
	static int   _indices[6];

	Unique<VertexArray>  _vertexArray;
	Ref<VertexBuffer> _vertexBuffer;
	Ref<IndexBuffer>  _indexBuffer;
	Unique<ShaderProgram> _program;
};


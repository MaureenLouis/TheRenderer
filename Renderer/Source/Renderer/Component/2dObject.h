#pragma once
#include "RenderObject.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Texture/Texture.h"
#include "Fundation/Ref/Unique.h"
#include "Fundation/Ref/Ref.h"


class Object2D : public RenderObject
{
public:
	Object2D();

	virtual void draw() override;
	virtual Unique<ShaderProgram>& shader() override
	{
		return _program;
	}

private:
	Unique<VertexArray>   _vertexArray;
	Ref<VertexBuffer>     _vertexBuffer;
	Ref<IndexBuffer>      _indexBuffer;
	Unique<ShaderProgram> _program;
	Unique<Texture2D>     _texture;
};
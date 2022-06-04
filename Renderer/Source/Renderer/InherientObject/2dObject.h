#pragma once
#include "InherientObject.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Texture/Texture.h"
#include "Fundation/Ref/Unique.h"
#include "Fundation/Ref/Ref.h"
#include "Renderer/Camera/TrackBall.h"

class Object2D : public InherientObject
{
public:
	Object2D(Ref<TrackBall>& trackBall);

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
	Ref<TrackBall>        _trackBall;
};
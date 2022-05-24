#pragma once
#include "Renderer/Shader/ShaderProgram.h"


class RenderObject
{
public:
	virtual ~RenderObject() {};
	virtual void draw() = 0;
	virtual Unique<ShaderProgram>& shader() = 0;
};
#pragma once

#include "Renderer/Shader/ShaderProgram.h"

class InherientObject
{
public:
	virtual ~InherientObject() {};
	virtual void draw() = 0;
	virtual Unique<ShaderProgram>& shader() = 0;
};



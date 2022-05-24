#pragma once
#include "PickingInterface.h"
#include "Renderer/Shader/ShaderProgram.h"

class ColorPicking : public PickingInterfaces
{
public:
	ColorPicking();

	virtual void drawStartCB(unsigned int drawIndex) override;

private:
	Unique<ShaderProgram> _shader;
};
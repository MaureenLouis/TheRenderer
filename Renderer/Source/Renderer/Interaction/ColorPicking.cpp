#include "stdafx.h"
#include "ColorPicking.h"

ColorPicking::ColorPicking()
{
	_shader = std::make_unique<ShaderProgram>("D:\\Projects\\TheRenderer\\Asset\\Shader\\InherentShader\\PickingShader.glsl");
}

void ColorPicking::drawStartCB(unsigned int drawIndex)
{
	// glUniform1ui(m_drawIndexLocation, drawIndex);
}

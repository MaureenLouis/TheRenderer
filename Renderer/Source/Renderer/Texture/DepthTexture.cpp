#include "stdafx.h"
#include "DepthTexture.h"

DepthTexture::DepthTexture(unsigned int width, unsigned int height)
{
	_width = width, _height = height;
	_channels = 1; // GL_RGB

	glGenTextures(1, &_handle);
	Self::bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
}

DepthTexture::~DepthTexture()
{
	glDeleteTextures(1, &_handle);
}


#pragma once
#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/DepthTexture.h"
#include "Renderer/Buffer/RenderBuffer.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();

	void bind();
	void unbind();
	unsigned int frameTextureHandle();

private:
	unsigned int _colorTexHandle;
	unsigned int _depthTexHandle;
	unsigned int _frameBufhandle;
	unsigned int _renderBufHandle;
	unsigned int _width;
	unsigned int _height;
};
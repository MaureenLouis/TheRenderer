#pragma once
#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/DepthTexture.h"
#include "Renderer/Buffer/RenderBuffer.h"

class FrameBuffer
{
	SELF(FrameBuffer);
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();

	void bind();
	void unbind();
	unsigned int handle() { return _handle; }

	void attachColor(GLenum attachment, Ref<Texture2D>& texture);
	void attachDepth(Ref<DepthTexture>& texture);
	void attachStencil(Ref<RenderBuffer>& texture);

	bool verifyFramebufferStatus();

private:
	unsigned int _handle;
	unsigned int _width, _height;
};
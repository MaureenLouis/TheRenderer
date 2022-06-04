#include "stdafx.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;

	// FBO
	glGenFramebuffers(1, &_frameBufhandle);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufhandle);

	// Texture attachment
	glGenTextures(1, &_colorTexHandle);
	glBindTexture(GL_TEXTURE_2D, _colorTexHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexHandle, 0);

	// Depth buffer attachment
	glGenTextures(1, &_depthTexHandle);
	glBindTexture(GL_TEXTURE_2D, _depthTexHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexHandle, 0);

	// Render buffer attachment
	glGenRenderbuffers(1, &_renderBufHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderBufHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBufHandle);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		APP_INFO("FBO complete!");
	}
}

FrameBuffer::~FrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &_frameBufhandle);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufhandle);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::frameTextureHandle()
{
	return _colorTexHandle;
}

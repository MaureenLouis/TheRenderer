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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexHandle, 0);

    // Depth attachment
	glGenTextures(1, &_depthTexHandle);
	glBindTexture(GL_TEXTURE_2D, _depthTexHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexHandle, 0);

	// Render attachment
	glGenRenderbuffers(1, &_renderBufHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderBufHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
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
	glBindBuffer(GL_FRAMEBUFFER, _frameBufhandle);
}

void FrameBuffer::unbind()
{
	glBindBuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::frameTextureHandle()
{
	return _colorTexHandle;
}

#include "stdafx.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;

	glGenFramebuffers(1, &_handle);
}

FrameBuffer::~FrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &_handle);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _handle);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachColor(GLenum attachment, Ref<Texture2D>& texture)
{
	texture->unbind();
	unsigned int handle = texture->handle();
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, handle, 0);
}

void FrameBuffer::attachDepth(Ref<DepthTexture>& texture)
{
	texture->unbind();
	unsigned int handle = texture->handle();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, handle, 0);
}

void FrameBuffer::attachStencil(Ref<RenderBuffer>& buffer)
{
	buffer->unbind();
	unsigned int handle = buffer->handle();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, handle);
}


bool FrameBuffer::verifyFramebufferStatus()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		return true;
	}
	return false;
}

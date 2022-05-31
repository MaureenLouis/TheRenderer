#include "stdafx.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;

	glGenFramebuffers(1, &_handle);
	Self::bind();
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
	unsigned int handle = texture->handle();
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, handle, 0);
	texture->unbind();
}

void FrameBuffer::attachDepth(Ref<Texture2D>& texture)
{
	unsigned int handle = texture->handle();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, handle, 0);
	texture->unbind();
}

void FrameBuffer::attachStencil(Ref<RenderBuffer>& buffer)
{
	unsigned int handle = buffer->handle();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, handle);
	buffer->unbind();
}


bool FrameBuffer::verifyFramebufferStatus()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		return true;
	}
	return false;
}

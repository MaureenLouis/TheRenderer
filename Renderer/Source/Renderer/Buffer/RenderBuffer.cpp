#include "stdafx.h"
#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height)
{
	_width = width, _height = height;
	glGenRenderbuffers(1, &_handle);
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

RenderBuffer::~RenderBuffer()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

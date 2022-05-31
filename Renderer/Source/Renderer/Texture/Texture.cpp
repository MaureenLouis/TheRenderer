#include "stdafx.h"
#include "Texture.h"
#include "TextureLoader.h"

static constexpr unsigned int getOpenGLChannels(int internalChannel)
{
	unsigned int channels = 0;
	switch (internalChannel)
	{
	case (GL_RGB): channels = 3; break;
	case (GL_RGBA): channels = 4; break;
	default: ASSERT(false, "Unknown opengl internal channels");
	}

	return channels;
}

Texture2D::Texture2D(const char* path)
{

	TextureLoader loader(path);
	_width = loader.textureWidth();
	_height = loader.textureHeight();
	_channels = loader.textureChannels();

	glGenTextures(1, &_handle);
	Self::bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, loader.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(unsigned int width, unsigned int height)
{
	_width = width, _height = height;
	_channels = getOpenGLChannels(GL_RGB); // GL_RGB

	glGenTextures(1, &_handle);
	Self::bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_handle);
}

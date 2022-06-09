#include "stdafx.h"
#include "TextureLoader.h"

TextureLoader::TextureLoader(const char* path, unsigned int channelDesired)
{
	_path = path;
	_data = stbi_load(_path, &_width, &_height, &_channels, channelDesired);
	if (!_data)
	{
		APP_ERROR("Fail to load image as texture");
		return;
	}

	if (_channels == 1)
	{
		_format = GL_RED;
	}
	else if (_channels == 3)
	{
		_format = GL_RGB;
	}
	else if (_channels == 4)
	{
		_format = GL_RGBA;
	}
}

TextureLoader::~TextureLoader()
{
	stbi_image_free(_data);
}




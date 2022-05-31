#include "stdafx.h"
#include "TextureLoader.h"

TextureLoader::TextureLoader(const char* path)
{
	_path = path;
	_data = stbi_load(_path, &_width, &_height, &_channels, 0);
	if (!_data)
	{
		APP_ERROR("Fail to load image as texture");
		return;
	}
}

TextureLoader::~TextureLoader()
{
	stbi_image_free(_data);
}


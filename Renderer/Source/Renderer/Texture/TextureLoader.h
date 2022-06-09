#pragma once

class TextureLoader
{
public:
	TextureLoader(const char* path, unsigned int channelDesired = 0u);
	~TextureLoader();

	int textureWidth() { return _width; }
	int textureHeight() { return _height; }
	unsigned int internalForamt() { return _format; }
	int textureChannels() { return _channels; };
	unsigned char* data() { return _data; };

private:
	int            _width;
	int            _height;
	int            _channels;
	unsigned char* _data;
	const char*    _path;
	unsigned int   _format;
};


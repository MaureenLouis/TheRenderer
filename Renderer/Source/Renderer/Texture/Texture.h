#pragma once

class Texture2D
{
	SELF(Texture2D);
public:

	Texture2D(const char* path);
	Texture2D(unsigned int width, unsigned int height);    // Empty texture with only memory allocation.
	~Texture2D();
	
	void bind() const
	{ glBindTexture(GL_TEXTURE_2D, _handle);}

	void unbind() const
	{ glBindTexture(GL_TEXTURE_2D, 0); }

	unsigned int handle() const
	{ return _handle; }

private:
	GLuint _handle;
	int    _width;
	int    _height;
	int    _channels;
};


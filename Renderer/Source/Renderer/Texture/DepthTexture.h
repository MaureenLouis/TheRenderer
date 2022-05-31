#pragma once

class DepthTexture
{
	SELF(DepthTexture);

public:
	DepthTexture(unsigned int width, unsigned int height);
	~DepthTexture();

	void bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _handle);
	}

	void unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int handle() const
	{
		return _handle;
	}

private:
	GLuint _handle;
	int    _width;
	int    _height;
	int    _channels;

};
#pragma once
class RenderBuffer
{
public:
	RenderBuffer(unsigned int width, unsigned int height);
	~RenderBuffer();

	unsigned int handle() { return _handle; }

	void bind() 
	{
		glBindRenderbuffer(GL_RENDERBUFFER, _handle);
	};

	void unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

private:
	unsigned int _handle;
	unsigned int _width ,_height;

};


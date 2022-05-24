#pragma once

class OpenGLContext
{
public:
	OpenGLContext(GLFWwindow* windowHandle);

	void init();
	void swapBuffers();

private:
	GLFWwindow* _windowHandle;
};
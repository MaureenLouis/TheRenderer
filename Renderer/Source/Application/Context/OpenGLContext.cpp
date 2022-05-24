#include "stdafx.h"
#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	:_windowHandle(windowHandle)
{
	
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(_windowHandle);

	int ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!ret)
	{
		APP_ERROR("Fail to load glad");
		return;
	}
}

void OpenGLContext::swapBuffers()
{
	glfwSwapBuffers(_windowHandle);
}

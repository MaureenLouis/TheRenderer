#include "stdafx.h"
#include "OpenGLLog.h"

#define CASE(buf, enum)			   \
case enum :						   \
	sprintf(buf, "%s", #enum);     \
	break

GLenum glCheckError(const char* file, const char* function, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		char buf[64] = { 0 };
		switch (errorCode)
		{
			CASE(buf, GL_INVALID_ENUM);
			CASE(buf, GL_INVALID_VALUE);
			CASE(buf, GL_INVALID_OPERATION);
			CASE(buf, GL_STACK_OVERFLOW);
			CASE(buf, GL_STACK_UNDERFLOW);
			CASE(buf, GL_OUT_OF_MEMORY);
			CASE(buf, GL_INVALID_FRAMEBUFFER_OPERATION);
		}

		char errMsgBuf[256];
		sprintf(errMsgBuf, "%s\nat File:%s\nat Function:%s\nat Line:%d",buf, file, function, line);
		CORE_ERROR(errMsgBuf);
	}

	return GLenum();
}

int glShaderCheckError(int handle, const char* file, const char* function, int line)
{
	int successed;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &successed);
	char infoLog[256] = { 0 };
	char errMsgBuf[256];
	if (successed != GL_TRUE)
	{
		glGetShaderInfoLog(handle, 512, NULL, infoLog);
		sprintf(errMsgBuf, "%s\nat File:%s\nat Function:%s\nat Line:%d", infoLog, file, function, line);
		CORE_ERROR(errMsgBuf);
	};

	return successed;
}

int glProgramCheckError(int handle, const char* file, const char* function, int line)
{
	int successed;
	glGetProgramiv(handle, GL_LINK_STATUS, &successed);
	char infoLog[256] = { 0 };
	char errMsgBuf[256];
	if (successed != GL_TRUE)
	{
		glGetProgramInfoLog(handle, 512, NULL, infoLog);
		sprintf(errMsgBuf, "%s\nat File:%s\nat Function:%s\nat Line:%d", infoLog, file, function, line);
		CORE_ERROR(errMsgBuf);
	};

	return successed;
}
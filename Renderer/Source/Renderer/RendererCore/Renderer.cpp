#include "stdafx.h"
#include "Renderer.h"


const unsigned char* Renderer::vender()
{
	return glGetString(GL_VENDOR);
}

const unsigned char* Renderer::rendererName()
{
	return glGetString(GL_RENDERER);
}

const unsigned char* Renderer::releaseVersion()
{
	return glGetString(GL_VERSION);
}

const unsigned char* Renderer::shadingLanguageVersion()
{
	return glGetString(GL_SHADING_LANGUAGE_VERSION);
}

const char* Renderer::maxPatchVertices()
{
	GLint maxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVertices);
	static char buf[8] = { 0 };
	::sprintf(buf, "%d", maxPatchVertices);
	return buf;
}

void Renderer::setPolygonMode(Config::PolygonMode polygonMode)
{
	if (polygonMode == Config::PolygonMode::Fill)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
	}
	else if (polygonMode == Config::PolygonMode::Line)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else
	{
		ASSERT(false, "Unknown polygon mode");
	}
}


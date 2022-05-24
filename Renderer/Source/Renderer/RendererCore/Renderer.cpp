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


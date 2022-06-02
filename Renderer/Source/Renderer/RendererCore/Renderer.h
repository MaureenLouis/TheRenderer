#pragma once

class Renderer
{
public:
	enum class ShadingMode : uint8_t
	{
		DefaultShading = 0,
		Wireframe = 1
	};

	static const unsigned char* vender();
	static const unsigned char* rendererName();
	static const unsigned char* releaseVersion();
	static const unsigned char* shadingLanguageVersion();
	static const  char* maxPatchVertices();

	static void setPolygonMode(Config::PolygonMode polygonMode);
};
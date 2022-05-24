#pragma once
#include "ShaderProgram.h"

class ShaderLoader
{
	SELF(ShaderLoader);
public:
	ShaderLoader(const char* path)
		: _path(path)
	{
		Self::load();
	}

	std::string vertexShader() { return _shaderSources[GL_VERTEX_SHADER]; };
	std::string fragmentShader() { return _shaderSources[GL_FRAGMENT_SHADER]; };;

private:
	std::string readFile(const char* path);
	void ShaderLoader::preProcess(const std::string& source);
	void load();

private:
	std::unordered_map<GLenum, std::string> _shaderSources;
	const char* _path;
};
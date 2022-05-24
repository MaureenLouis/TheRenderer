#include "stdafx.h"
#include "ShaderLoader.h"

static GLenum shaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
	{
		return GL_VERTEX_SHADER;
	}

	if (type == "fragment" || type == "pixel")
	{
		return GL_FRAGMENT_SHADER;
	}

	assert(false);
	return 0;
}

void ShaderLoader::load()
{
	std::string src = Self::readFile(_path);
	Self::preProcess(src);
}

std::string ShaderLoader::readFile(const char* path)
{
	std::string result;
	std::ifstream in(path, std::ios::in, std::ios::binary);
	if (in)
	{
		// 确定 std::string 的大小
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());

		// 读入内容
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
	{
		CORE_ERROR("Could not open file '{0}'", path);
	}

	return result;
}

void ShaderLoader::preProcess(const std::string& source)
{

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);

	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		assert(eol != std::string::npos);

		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		assert(shaderTypeFromString(type));

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLinePos);

		_shaderSources[shaderTypeFromString(type)] =
			source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ?
					source.size() - 1 : nextLinePos));
	}
}
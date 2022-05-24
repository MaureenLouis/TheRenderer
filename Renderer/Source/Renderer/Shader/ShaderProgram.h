#pragma once
#include "Fundation/Log/OpenGLLog.h"
#include "Fundation/Type/Enumerate.h"
#include "Core/Compiler/Inline.h"

class ShaderProgram 
{
	friend class ShaderLoader;
public:
	Enumerate(ShaderTag, uint8_t, 
		VertexShader = 0, 
		FragmentShader = 1);

	ShaderProgram(const char* vertexShaderSouce, const char* fragmentShaderSource);
	ShaderProgram(const char* path);

	virtual ~ShaderProgram();

	ALWAYS_INLINE void use() const
	{
		glUseProgram(_shaderProgramHandle);
	}

	template <typename T>
	void setUniform(const char* uniformName, const T& val)
	{
		use();
		int location = glGetUniformLocation(_shaderProgramHandle, uniformName);
		setUniform(location, val);
	}

	void setUniform(const int location, const glm::vec4& val);
	void setUniform(const int location, const glm::mat4& val);
	void setUniform(const int location, const int val);

private:
	void compileShader(int shaderHandle);
	void linkShader();

private:
	int _vertexShaderHandle;
	int _fragmentShaderHandle;
	int _shaderProgramHandle;
};
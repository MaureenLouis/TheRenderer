#include "stdafx.h"
#include "ShaderProgram.h"
#include "ShaderLoader.h"

ShaderProgram::ShaderProgram(const char* vertexShaderSouce, const char* fragmentShaderSource)
{
	if (vertexShaderSouce == nullptr || fragmentShaderSource == nullptr)
	{
		APP_ERROR("Shader souce could not be null.");
		return;
	}

	_vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShaderHandle, 1, &vertexShaderSouce, nullptr);
	compileShader(_vertexShaderHandle);

	_fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShaderHandle, 1, &fragmentShaderSource, nullptr);
	compileShader(_fragmentShaderHandle);

	_tessellationControlShaderHandle = 0;
	_tessellationEvaluateShaderHandle = 0;


	linkShader();
}

ShaderProgram::ShaderProgram(const char* path)
{
	if (path == nullptr)
	{
		APP_ERROR("Shader source file path could not be null.");
		return;
	}

	ShaderLoader loader(path);
	std::string vertexShaderSource = loader.vertexShader();
	std::string fragmentShaderSource = loader.fragmentShader();
	std::string tcShaderSoucr = loader.tessellationControlShader();
	std::string teShaderSoucr = loader.tessellationEvaluateShader();
	const char* vSrc = vertexShaderSource.c_str();
	const char* fSrc = fragmentShaderSource.c_str();
	const char* tcSrc = tcShaderSoucr.c_str();
	const char* teSrc = teShaderSoucr.c_str();


	_vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShaderHandle, 1, &vSrc, nullptr);
	compileShader(_vertexShaderHandle);

	_fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShaderHandle, 1, &fSrc, nullptr);
	compileShader(_fragmentShaderHandle);

	_tessellationControlShaderHandle = 0;
	_tessellationEvaluateShaderHandle = 0;

	int ret = ::strcmp(tcSrc, "");
	if (ret != 0)
	{
	    _tessellationControlShaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
	    glShaderSource(_tessellationControlShaderHandle, 1, &tcSrc, nullptr);
	    compileShader(_tessellationControlShaderHandle);
	}

	if (ret != 0)
	{
	    _tessellationEvaluateShaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
	    glShaderSource(_tessellationEvaluateShaderHandle, 1, &teSrc, nullptr);
	    compileShader(_tessellationEvaluateShaderHandle);
	}

	linkShader();
}



ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_shaderProgramHandle);
}

void ShaderProgram::linkShader()
{
	_shaderProgramHandle = glCreateProgram();
	glAttachShader(_shaderProgramHandle, _vertexShaderHandle);
	glAttachShader(_shaderProgramHandle, _fragmentShaderHandle);
	if (_tessellationControlShaderHandle != 0 && _tessellationEvaluateShaderHandle != 0)
	{
		glAttachShader(_shaderProgramHandle, _tessellationControlShaderHandle);
		glAttachShader(_shaderProgramHandle, _tessellationEvaluateShaderHandle);
	}
	glLinkProgram(_shaderProgramHandle);
	glProgramCheck(_shaderProgramHandle);

	glDeleteShader(_vertexShaderHandle);
	glDeleteShader(_fragmentShaderHandle);
	glDeleteShader(_tessellationControlShaderHandle);
	glDeleteShader(_tessellationEvaluateShaderHandle);

}



void ShaderProgram::compileShader(int shaderHandle)
{
	glCompileShader(shaderHandle);
	glShaderCheck(shaderHandle);
}

void ShaderProgram::setUniform(const int location, const glm::vec4& val)
{
	glUniform4f(location, val.x, val.y, val.z, val.w);
}

void ShaderProgram::setUniform(const int location, const glm::vec3& val)
{
	glUniform3f(location, val.x, val.y, val.z);
}

void ShaderProgram::setUniform(const int location, const glm::mat4& val)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

void ShaderProgram::setUniform(const int location, const int val)
{
	glUniform1i(location, val);
}

void ShaderProgram::setUniform(const int location, const float val)
{
	glUniform1f(location, val);
}

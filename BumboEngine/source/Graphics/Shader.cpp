#include <glew/glew.h>

#include "Graphics/Shader.h"
#include "IO/File.h"

Shader::Shader()
{
	programId = glCreateProgram();
}

Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(programId);
}

void Shader::Compile()
{
	glLinkProgram(programId);
	isCompiled = true;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetFragmentShader(GLint shaderId)
{
	if (!isCompiled)
	{
		fragmentShader = shaderId;
		glAttachShader(programId, shaderId);
	}
}

void Shader::SetVertexShader(GLint shaderId)
{
	if (!isCompiled)
	{
		vertexShader = shaderId;
		glAttachShader(programId, shaderId);
	}
}

GLint Shader::FromFile(const char *shaderPath, int shaderType)
{
	return FromFile((char*)shaderPath, shaderType);
}
GLint Shader::FromFile(char *shaderPath, int shaderType)
{
	char *content = File::LoadText(shaderPath);

	unsigned int shaderId;
	shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &content, NULL);
	glCompileShader(shaderId);

	return shaderId;
}
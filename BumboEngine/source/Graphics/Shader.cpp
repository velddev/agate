#include <glew/glew.h>

#include <vector>

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

void Shader::SetUniformMat4(const char *fieldName, glm::mat4 matrix)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
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

	GLint isCompiled = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

		std::string str(errorLog.begin(), errorLog.end());

		printf(str.c_str());
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(shaderId); // Don't leak the shader.
		return 0;
	}
	return shaderId;
}
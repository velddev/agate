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
	if (textureId != 0)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
}

void Shader::Compile()
{
	glLinkProgram(programId);
	isCompiled = true;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint Shader::GetProgramId()
{
	return programId;
}

void Shader::Load(char *filePath)
{
	std::string extension = std::string(filePath);
	int offset = extension.find_last_of(".");
	extension = extension.substr(offset + 1);

	GLint shaderId = FromFile(filePath);

	if (extension == "vs")
	{
		vertexShader = shaderId;
	}
	else if (extension == "fs")
	{
		fragmentShader = shaderId;
	}
}

void Shader::SetFragmentShader(GLint shaderId)
{
	if (!isCompiled)
	{
		fragmentShader = shaderId;
		glAttachShader(programId, shaderId);
	}
}

void Shader::SetTexture(GLuint textureHandle)
{
	textureId = textureHandle;
}

void Shader::SetVertexShader(GLint shaderId)
{
	if (!isCompiled)
	{
		vertexShader = shaderId;
		glAttachShader(programId, shaderId);
	}
}

void Shader::SetUniformVec3(const char *fieldName, glm::vec3 vector)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniform3f(id, vector.x, vector.y, vector.z);
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

void Shader::Unbind()
{
	glUseProgram(0);
}

GLint Shader::FromFile(const char *shaderPath)
{
	return FromFile((char*)shaderPath);
}
GLint Shader::FromFile(char *shaderPath)
{
	char *content = File::LoadText(shaderPath);
	unsigned int shaderId;

	std::string extension = std::string(shaderPath);
	int offset = extension.find_last_of(".");
	extension = extension.substr(offset + 1);

	GLint shaderType = 0;

	if (extension == "vs")
	{
		shaderType = GL_VERTEX_SHADER;
	}
	else if (extension == "fs")
	{
		shaderType = GL_FRAGMENT_SHADER;
	}

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

		glDeleteShader(shaderId);
		return 0;
	}
	return shaderId;
}
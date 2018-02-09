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
	if (textures.size() > 0)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
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
	GLint shaderId = FromFile(filePath);
	GLint shaderType = GetType(filePath);

	if (shaderType == GL_VERTEX_SHADER)
	{
		vertexShader = shaderId;
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
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

void Shader::SetTexture(GLuint textureHandle, int index)
{
	while (textures.size() <= index)
	{
		textures.push_back(textureHandle);
	}
	textures[index] = textureHandle;
}

void Shader::SetVertexShader(GLint shaderId)
{
	if (!isCompiled)
	{
		vertexShader = shaderId;
		glAttachShader(programId, shaderId);
	}
}

void Shader::SetUniform1i(const char * fieldName, int i)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniform1i(id, i);
}

void Shader::SetUniform1f(const char * fieldName, float f)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniform1f(id, f);
}

void Shader::SetUniform3f(const char *fieldName, glm::vec3 vector)
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

	GLint shaderType = GetType(shaderPath);

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

GLint Shader::GetType(char *path)
{
	std::string extension = std::string(path);
	int offset = extension.find_last_of(".");
	extension = extension.substr(offset + 1);

	if (extension == "vert")
	{
		return GL_VERTEX_SHADER;
	}
	else if (extension == "frag")
	{
		return GL_FRAGMENT_SHADER;
	}
}

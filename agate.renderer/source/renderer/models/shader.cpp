#include <vector>

#include "IO/filesystem/File.h"
#include "renderer/models/shader.h"

using namespace agate::renderer;

Shader::Shader()
	: fragmentShader(GL_NONE), vertexShader(GL_NONE), ShaderBase()
{
}

Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(GetProgramId());
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
	assert(!isCompiled, "Shader was already compiled!");
	glLinkProgram(GetProgramId());
	isCompiled = true;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Load(char *filePath)
{

}

void Shader::SetFragmentShader(GLint shaderId)
{
	if (!isCompiled)
	{
		fragmentShader = shaderId;
		glAttachShader(GetProgramId(), shaderId);
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
		glAttachShader(GetProgramId(), shaderId);
	}
}

void Shader::Unbind()
{
	glUseProgram(0);
}

GLint Shader::IdFromFile(char* shaderPath)
{
	char* content = File::LoadText(shaderPath);
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

GLint Shader::IdFromFile(const char* shaderPath)
{
	return IdFromFile((char*)shaderPath);
}

Shader* Shader::FromFile(const char *shaderPath)
{
	return FromFile((char*)shaderPath);
}
Shader* Shader::FromFile(char *shaderPath)
{
	auto shader = new Shader();
	GLint shaderId = IdFromFile(shaderPath);
	GLint shaderType = GetType(shaderPath);

	if (shaderType == GL_VERTEX_SHADER)
	{
		shader->vertexShader = shaderId;
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		shader->fragmentShader = shaderId;
	}

	return shader;
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

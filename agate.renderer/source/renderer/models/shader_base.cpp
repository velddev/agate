#include <glew/glew.h>

#include "renderer/models/shader_base.h"

using namespace agate::renderer;

ShaderBase::ShaderBase()
{
	programId = glCreateProgram();
}

ShaderBase::~ShaderBase()
{
}

GLint ShaderBase::GetProgramId()
{
	return programId;
}

void ShaderBase::SetUniform1i(const char* fieldName, int i)
{
	GLint id = GetUniformLocation(fieldName);

	if (id == -1)
	{
		printf("err | uniform '%s' couldn't been found\n", fieldName);
	}

	glUniform1i(id, i);
}

void ShaderBase::SetUniform1f(const char* fieldName, float f)
{
	GLint id = GetUniformLocation(fieldName);

	if (id == -1)
	{
		printf("err | uniform '%s' couldn't been found\n", fieldName);
	}

	glUniform1f(id, f);
}

void ShaderBase::SetUniform3f(const char* fieldName, glm::vec3 vector)
{
	GLint id = GetUniformLocation(fieldName);

	if (id == -1)
	{
		printf("err | uniform '%s' couldn't been found\n", fieldName);
	}

	glUniform3f(id, vector.x, vector.y, vector.z);
}

void ShaderBase::SetUniformMat4(const char* fieldName, glm::mat4 matrix)
{
	GLint id = GetUniformLocation(fieldName);

	if (id == -1)
	{
		printf("err | uniform '%s' couldn't been found\n", fieldName);
	}

	glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
}

GLint agate::renderer::ShaderBase::GetUniformLocation(const char* fieldName)
{
	if (uniformCache.find(fieldName) != uniformCache.end()) {
		return uniformCache[fieldName];
	}

	printf("fetching uniform %s", fieldName);
	GLint id = glGetUniformLocation(programId, fieldName);
	uniformCache.insert({ fieldName, id });
	return id;
}

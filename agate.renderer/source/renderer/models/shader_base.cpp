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
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniform1i(id, i);
}

void ShaderBase::SetUniform1f(const char* fieldName, float f)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniform1f(id, f);
}

void ShaderBase::SetUniform3f(const char* fieldName, glm::vec3 vector)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniform3f(id, vector.x, vector.y, vector.z);
}

void ShaderBase::SetUniformMat4(const char* fieldName, glm::mat4 matrix)
{
	GLint id = glGetUniformLocation(programId, fieldName);

	if (id == -1)
	{
		printf("err | uniform couldn't been found\n");
	}

	glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
}

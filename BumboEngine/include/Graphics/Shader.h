#pragma once
#include <glfw/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "Engine/Resources/Loadable.h"

class Shader : Loadable
{
public:
	Shader();
	
	~Shader();

	void Bind();

	void Compile();
	
	GLint GetProgramId();

	virtual void Load(char *filePath);

	void SetFragmentShader(GLint shaderId);

	void SetTexture(GLuint textureHandle);

	void SetVertexShader(GLint shaderId);

	void SetUniformVec3(const char *fieldName, glm::vec3 vector);
	
	void SetUniformMat4(const char *fieldName, glm::mat4 matrix);

	void Unbind();

	static GLint FromFile(const char *shaderPath);
	static GLint FromFile(char *shaderPath);

private:
	GLint fragmentShader;
	GLint vertexShader;
	GLint programId;
	GLuint textureId;

	bool isCompiled = false;
};
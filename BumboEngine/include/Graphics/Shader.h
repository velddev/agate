#pragma once
#include <glfw/glfw3.h>
#include <glm/mat4x4.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	void Bind();
	void Compile();
	void Unbind();

	void SetFragmentShader(GLint shaderId);
	void SetVertexShader(GLint shaderId);

	void SetUniformMat4(const char *fieldName, glm::mat4 matrix);

	static GLint FromFile(const char *shaderPath, int shaderType);
	static GLint FromFile(char *shaderPath, int shaderType);

private:
	GLint fragmentShader;
	GLint vertexShader;
	GLint programId;

	bool isCompiled = false;
};
#pragma once
#include <glfw/glfw3.h>

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

	static GLint FromFile(const char *shaderPath, int shaderType);
	static GLint FromFile(char *shaderPath, int shaderType);

private:
	GLint fragmentShader;
	GLint vertexShader;
	GLint programId;

	bool isCompiled = false;
};
#pragma once
#include <glew/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

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

	void SetTexture(GLuint textureHandle, int index = 0);

	void SetVertexShader(GLint shaderId);

	void SetUniform1i(const char *fieldName, int i);
	void SetUniform1f(const char *fieldName, float f);
	void SetUniform3f(const char *fieldName, glm::vec3 vector);
	
	void SetUniformMat4(const char *fieldName, glm::mat4 matrix);

	void Unbind();

	static GLint FromFile(const char *shaderPath);
	static GLint FromFile(char *shaderPath);

private:
	GLint fragmentShader;
	GLint vertexShader;
	GLint programId;
	std::vector<GLint> textures;

	bool isCompiled = false;

	static GLint GetType(char *path);
};
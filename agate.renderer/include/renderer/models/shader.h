#pragma once
#include <glew/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#include "shader_base.h"

namespace agate::renderer
{
	class Shader : public ShaderBase
	{
	public:
		Shader();
		~Shader();

		void Bind();

		void Compile();

		void Load(char* filePath);

		void SetFragmentShader(GLint shaderId);

		void SetTexture(GLuint textureHandle, int index = 0);

		void SetVertexShader(GLint shaderId);

		void Unbind();

		static GLint IdFromFile(const char* shaderPath);
		static GLint IdFromFile(char* shaderPath);
		static Shader* FromFile(const char* shaderPath);
		static Shader* FromFile(char* shaderPath);

	private:
		GLint fragmentShader;
		GLint vertexShader;
		std::vector<GLint> textures;

		bool isCompiled = false;

		static GLint GetType(char* path);
	};
}
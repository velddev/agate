#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>

namespace agate::renderer
{
	class ShaderBase
	{
	public:
		ShaderBase();
		~ShaderBase();

		GLint GetProgramId();

		void SetUniform1i(const char* fieldName, int i);
		void SetUniform1f(const char* fieldName, float f);
		void SetUniform3f(const char* fieldName, glm::vec3 vector);

		void SetUniformMat4(const char* fieldName, glm::mat4 matrix);

	protected:
		GLint GetUniformLocation(const char* fieldName);

	private:
		std::map<std::string, GLint> uniformCache;

		GLint programId;
	};
}


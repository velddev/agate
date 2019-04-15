#pragma once
#include "renderer/Texture.h"

#include <glm/vec3.hpp>

namespace agate::renderer
{
	class Material
	{
	public:
		Material() = default;
		~Material() = delete;

		glm::vec3 ambient;

		Texture* diffuse;
		glm::vec3 diffuseColor;

		Texture* specular;
		glm::vec3 specularColor;
		float shininess = 1.f;

	private:
	};
}
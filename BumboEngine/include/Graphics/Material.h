#pragma once
#include "Graphics/Texture.h"

#include <glm/vec3.hpp>

class Material
{
public:
	Material();
	~Material();

	glm::vec3 ambient;
	
	Texture *diffuse;
	glm::vec3 diffuseColor;

	Texture *specular;
	glm::vec3 specularColor;
	float shininess = 32.0f;

private:
};


#pragma once
#include <glm/vec4.hpp>

class Material
{
public:
	Material();
	~Material();

	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	float shininessColor;
	glm::vec4 specularColor;

private:
};


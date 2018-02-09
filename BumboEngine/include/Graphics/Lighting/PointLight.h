#pragma once
#include <glm/vec3.hpp>

class PointLight
{
public:
	PointLight();
	~PointLight();

	glm::vec3 GetColor();
	
	float GetRadius();

	void SetColor(glm::vec3 color);

	void SetRadius(float radius);

private:
	glm::vec3 color;
	float radius;
};

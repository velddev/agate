#pragma once
#include "Graphics/Transform.h"

#include <glm/vec3.hpp>

class PointLight
{
public:
	PointLight();
	~PointLight();

	glm::vec3 GetColor();
	
	float GetIntensity();

	float GetRadius();

	Transform *GetTransform();

	void SetColor(glm::vec3 color);

	void SetIntensity(float intensity);

	void SetRadius(float radius);

private:
	glm::vec3 color;
	float intensity;
	float radius;
	Transform *transform = new Transform();
};

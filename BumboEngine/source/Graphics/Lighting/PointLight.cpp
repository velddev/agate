#include "Graphics/Lighting/PointLight.h"

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

glm::vec3 PointLight::GetColor()
{
	return color;
}

float PointLight::GetRadius()
{
	return radius;
}

void PointLight::SetColor(glm::vec3 color)
{
	this->color = color;
}

void PointLight::SetRadius(float radius)
{
	this->radius = radius;
}
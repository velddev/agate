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

float PointLight::GetIntensity()
{
	return intensity;
}

float PointLight::GetRadius()
{
	return radius;
}

Transform *PointLight::GetTransform()
{
	return transform;
}

void PointLight::SetColor(glm::vec3 color)
{
	this->color = color;
}

void PointLight::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

void PointLight::SetRadius(float radius)
{
	this->radius = radius;
}
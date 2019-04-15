#include "renderer/lighting/LightSource.h"

using namespace agate::renderer;

LightSource::LightSource()
{
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetColor()
{
	return color;
}

float LightSource::GetIntensity()
{
	return intensity;
}

Transform *LightSource::GetTransform()
{
	return transform;
}

void LightSource::SetColor(glm::vec3 color)
{
	this->color = color;
}

void LightSource::SetIntensity(float intensity)
{
	this->intensity = intensity;
}
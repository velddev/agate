#include "renderer/lighting/DirectionalLight.h"

using namespace agate::renderer;

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

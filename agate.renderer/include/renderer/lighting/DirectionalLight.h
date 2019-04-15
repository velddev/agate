#pragma once
#include <glm/vec3.hpp>

#include "renderer/lighting/LightSource.h"

namespace agate::renderer
{
	class DirectionalLight : public LightSource
	{
	public:
		DirectionalLight();
		~DirectionalLight();

		glm::vec3 GetDirection();

		void SetDirection(glm::vec3 direction);

	private:
		glm::vec3 direction;
	};
}
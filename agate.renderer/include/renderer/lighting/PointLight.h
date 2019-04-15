#pragma once
#include "renderer/Lighting/LightSource.h"

#include <glm/vec3.hpp>

namespace agate::renderer
{
	class PointLight : public LightSource
	{
	public:
		PointLight();
		~PointLight();

		float GetLinear();
		float GetQuadratic();
		float GetRange();

		void SetLinear(float linear);
		void SetQuadratic(float quadratic);
		void SetRange(float range);

	protected:
		float range = 0.f;
		float linear = 0.35f;
		float quadratic = 0.44f;
	};
}
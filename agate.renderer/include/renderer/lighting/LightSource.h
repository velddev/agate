#pragma once
#include "renderer/Transform.h"

namespace agate::renderer 
{
	class LightSource
	{
	public:
		LightSource();
		~LightSource();

		glm::vec3 GetColor();

		float GetIntensity();

		Transform* GetTransform();

		void SetColor(glm::vec3 color);

		void SetIntensity(float intensity);

	protected:
		glm::vec3 color = { 1.0f, 1.0f, 1.0f };
		float intensity = 1.0f;
		Transform* transform = new Transform();
	};
}

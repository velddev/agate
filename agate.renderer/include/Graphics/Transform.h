#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace agate
{
	namespace renderer
	{
		class Transform
		{
		public:
			Transform() = default;
			~Transform() = default;

			const glm::mat4 GetModelMatrix();
			const glm::mat4 GetRotationMatrix();
			const glm::mat4 GetTranslationMatrix();
			const glm::mat4 GetScaleMatrix();

			const glm::vec3 GetPosition();
			const glm::vec3 GetRotation();
			const glm::vec3 GetScale();

			void SetPosition(glm::vec3 newPosition);
			void SetRotation(glm::vec3 newRotation);
			void SetScale(glm::vec3 newScale);

			void Translate(glm::vec3 addedPosition);
			void Rotate(glm::vec3 addedRotation);

		private:
			glm::mat4 translationMatrix;
			glm::mat4 scaleMatrix;

			glm::quat rotationQuaternion;

			glm::mat4 modelMatrix;

			bool hasChanged = true;
		};
	}
}
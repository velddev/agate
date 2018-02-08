#include "Graphics/Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetModelMatrix()
{
	if (hasChanged)
	{
		modelMatrix = GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
	}
	return modelMatrix;
}

glm::mat4 Transform::GetRotationMatrix()
{
	return glm::toMat4(rotationQuaternion);
}

glm::mat4 Transform::GetTranslationMatrix()
{
	return translationMatrix;
}

glm::mat4 Transform::GetScaleMatrix()
{
	return scaleMatrix;
}

glm::vec3 Transform::GetPosition()
{
	return { translationMatrix[0][4], translationMatrix[1][4], translationMatrix[2][4] };
}

glm::vec3 Transform::GetRotation()
{
	return glm::eulerAngles(rotationQuaternion);
}

glm::vec3 Transform::GetScale()
{
	return { scaleMatrix[0][0], scaleMatrix[1][1], scaleMatrix[2][2] };
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	translationMatrix[0][4] = newPosition.x;
	translationMatrix[1][4] = newPosition.y;
	translationMatrix[2][4] = newPosition.z;
	hasChanged = true;
}

void Transform::SetRotation(glm::vec3 newRotation)
{
	rotationQuaternion = glm::quat(newRotation);
}

void Transform::SetScale(glm::vec3 newScale)
{
	scaleMatrix[0][0] = newScale.x;
	scaleMatrix[1][1] = newScale.y;
	scaleMatrix[2][2] = newScale.z;
	hasChanged = true;
}

void Transform::Translate(glm::vec3 addedPosition)
{
	SetPosition(GetPosition() + addedPosition);
}

void Transform::Rotate(glm::vec3 addedRotation)
{
	rotationQuaternion = glm::quat(GetRotation() + addedRotation);
}

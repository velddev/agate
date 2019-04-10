#include <glm/gtx/quaternion.hpp>
#include "Graphics/Transform.h"

using namespace agate::renderer;
using namespace glm;

const mat4 Transform::GetModelMatrix()
{
	if (hasChanged)
	{
		modelMatrix = GetTranslationMatrix() 
			* GetRotationMatrix() 
			* GetScaleMatrix();
		hasChanged = false;
	}
	return modelMatrix;
}

const mat4 Transform::GetRotationMatrix()
{
	return toMat4(rotationQuaternion);
}

const mat4 Transform::GetTranslationMatrix()
{
	return translationMatrix;
}

const mat4 Transform::GetScaleMatrix()
{
	return scaleMatrix;
}

const vec3 Transform::GetPosition()
{
	return 
	{ 
		translationMatrix[3][0], 
		translationMatrix[3][1], 
		translationMatrix[3][2] 
	};
}

const vec3 Transform::GetRotation()
{
	vec3 euler = eulerAngles(rotationQuaternion);
	return vec3(
		degrees(euler.x),
		degrees(euler.y),
		degrees(euler.z));
}

const vec3 Transform::GetScale()
{
	return 
	{ 
		scaleMatrix[0][0], 
		scaleMatrix[1][1], 
		scaleMatrix[2][2] 
	};
}

void Transform::SetPosition(vec3 newPosition)
{
	translationMatrix[3][0] = newPosition.x;
	translationMatrix[3][1] = newPosition.y;
	translationMatrix[3][2] = newPosition.z;
	hasChanged = true;
}

void Transform::SetRotation(vec3 newRotation)
{
	rotationQuaternion = quat(
		vec3(radians(newRotation.x), 
			radians(newRotation.y), 
			radians(newRotation.z)));
	hasChanged = true;
}

void Transform::SetScale(vec3 newScale)
{
	scaleMatrix[0][0] = newScale.x;
	scaleMatrix[1][1] = newScale.y;
	scaleMatrix[2][2] = newScale.z;
	hasChanged = true;
}

void Transform::Translate(vec3 addedPosition)
{
	SetPosition(GetPosition() + addedPosition);
}

void Transform::Rotate(vec3 addedRotation)
{
	SetRotation(GetRotation() + addedRotation);
}

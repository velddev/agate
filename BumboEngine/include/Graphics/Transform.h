#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
	Transform();
	~Transform();

	glm::mat4 GetModelMatrix();
	glm::mat4 GetRotationMatrix();
	glm::mat4 GetTranslationMatrix();
	glm::mat4 GetScaleMatrix();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

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
	
	bool hasChanged;
};
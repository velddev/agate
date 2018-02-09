#include "Graphics/RenderObject.h"
#include "Graphics/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include "..\..\include\Graphics\RenderObject.h"

RenderObject::RenderObject(RenderSystem *system)
	: renderSystem(system)
{}

RenderObject::~RenderObject()
{
}

void RenderObject::Draw()
{
	glm::mat4 modelMatrix = transform->GetModelMatrix();
	glm::mat4 mvpMatrix =
		glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f) *
		glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		modelMatrix;

	model->GetShader()->Bind();

	model->GetShader()->SetUniformMat4("MVP", mvpMatrix);
	model->GetShader()->SetUniformMat4("model", modelMatrix);
	model->GetShader()->SetUniformVec3("ambientColor", renderSystem->GetAmbientColor());

	model->Draw();

	model->GetShader()->Unbind();
}

Transform * RenderObject::GetTransform()
{
	return transform;
}

void RenderObject::SetModel(Model * model)
{
	this->model = model;
}

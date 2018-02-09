#include "Graphics/RenderObject.h"
#include "Graphics/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

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
	model->GetShader()->SetUniform1f("renderSystem.ambientIntensity", renderSystem->GetAmbientIntensity());

	model->GetShader()->SetUniform3f("material.ambient", material->ambient);

	model->GetShader()->SetUniform1i("material.diffuse", 0);
	model->GetShader()->SetUniform1i("material.specular", 1);
	model->GetShader()->SetUniform1f("material.shininess", material->shininess);

	model->GetShader()->SetUniform3f("viewPos", glm::vec3());

	PointLight *pl = renderSystem->GetClosestLight(transform->GetPosition());

	if (pl != nullptr)
	{
		model->GetShader()->SetUniform3f("light.position", pl->GetTransform()->GetPosition());
		model->GetShader()->SetUniform3f("light.color", pl->GetColor() * pl->GetIntensity());
	}
	else
	{
		model->GetShader()->SetUniform3f("light.position", glm::vec3());
		model->GetShader()->SetUniform3f("light.color", glm::vec3());
	}

	model->Draw();

	model->GetShader()->Unbind();
}

Material * RenderObject::GetMaterial()
{
	return material;
}

Transform * RenderObject::GetTransform()
{
	return transform;
}

void RenderObject::SetModel(Model * model)
{
	this->model = model;
}

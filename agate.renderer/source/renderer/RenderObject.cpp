#include "renderer/RenderObject.h"
#include "renderer/models/shader.h"
#include "renderer/RenderSystem.h"

#include <glm/gtc/matrix_transform.hpp>
#include <sstream>

using namespace agate::renderer;
using namespace glm;

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

	DirectionalLight *dirLight = renderSystem->GetDirectionalLight();

	model->GetShader()->SetUniform1f("dirLight.intensity", dirLight->GetIntensity());
	model->GetShader()->SetUniform3f("dirLight.direction", dirLight->GetDirection());
	model->GetShader()->SetUniform3f("dirLight.diffuse", dirLight->GetDirection());

	std::vector<PointLight*> lights = renderSystem->GetAllLights(transform->GetPosition());

	model->GetShader()->SetUniform1i("pointLightCount", lights.size());

	for (int i = 0; i < lights.size(); i++)
	{
		std::string index = std::to_string(i);
		model->GetShader()->SetUniform3f(("pointLights[" + index + "].position").c_str(), lights[i]->GetTransform()->GetPosition());
		model->GetShader()->SetUniform1f(("pointLights[" + index + "].constant").c_str(), lights[i]->GetIntensity());
		model->GetShader()->SetUniform1f(("pointLights[" + index + "].linear").c_str(), lights[i]->GetLinear());
		model->GetShader()->SetUniform1f(("pointLights[" + index + "].quadratic").c_str(), lights[i]->GetQuadratic());
		model->GetShader()->SetUniform3f(("pointLights[" + index + "].diffuse").c_str(), lights[i]->GetColor());
	}

	model->Draw();

	model->GetShader()->Unbind();
}

Material *RenderObject::GetMaterial()
{
	return material;
}

Transform *RenderObject::GetTransform()
{
	return transform;
}

void RenderObject::SetModel(Model * model)
{
	this->model = model;
}

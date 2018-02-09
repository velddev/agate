#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glfw/glfw3.h>

#include "Graphics/Lighting/PointLight.h"

class RenderObject;
class Model;

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Add(RenderObject *model);
	RenderObject *AddModel(Model *model);

	GLuint CreateRenderTarget();
	void ClearRenderTarget();

	glm::vec3 GetAmbientColor();

	virtual void Render();

	void UseRenderTarget(GLuint id, glm::vec2 size);
	
	void SetAmbientColor(glm::vec3 color);

private:
	GLuint renderTargetId = 0;
	GLuint renderTargetTextureId = 0;

	std::vector<PointLight*> lights;
	std::vector<RenderObject*> renderableModels;

	glm::vec3 ambientColor;
};
#pragma once
#include <vector>

#include "Graphics/Model.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Add(Model *model);

	GLuint CreateRenderTarget();
	void ClearRenderTarget();

	virtual void Render();

	void UseRenderTarget(GLuint id, glm::vec2 size);
	
private:
	GLuint renderTargetId = 0;
	GLuint renderTargetTextureId = 0;

	std::vector<Model*> renderableModels;
};
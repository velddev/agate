#pragma once
#include "Graphics/RenderSystem.h"
#include "Graphics/Model.h"
#include "Graphics/Transform.h"

class RenderObject
{
public:
	RenderObject(RenderSystem *system);
	~RenderObject();

	void Draw();

	Transform *GetTransform();

	void SetModel(Model *model);

private:
	Model *model;
	RenderSystem *renderSystem;
	Transform *transform = new Transform();
};
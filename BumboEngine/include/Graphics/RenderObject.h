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

	Material *GetMaterial();

	Transform *GetTransform();

	void SetModel(Model *model);

private:
	Material *material = new Material();
	Model *model;
	RenderSystem *renderSystem;
	Transform *transform = new Transform();
};
#pragma once
#include "RenderSystem.h"
#include "Material.h"
#include "Model.h"
#include "Transform.h"

namespace agate::renderer
{
	class RenderObject
	{
	public:
		RenderObject(RenderSystem* system);
		~RenderObject();

		void Draw();

		Material* GetMaterial();

		Transform* GetTransform();

		void SetModel(Model* model);

	private:
		Material* material = new Material();
		Model* model;
		RenderSystem* renderSystem;
		Transform* transform = new Transform();
	};
}
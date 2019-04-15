#pragma once
#include "renderer/Transform.h"
#include "renderer/models/shader.h"
#include "renderer/Mesh.h"
#include "renderer/Material.h"
#include "renderer/RenderSystem.h"

#include "Engine/Resources/Loadable.h"

#include <string>
#include <vector>

namespace agate::renderer
{
	class Model
	{
	public:
		Model();
		~Model();

		void Draw();

		Shader* GetShader();

		virtual void Load(char* filePath);

		void SetShader(Shader* shader);

		static Model* FromFile(const char* filePath);
		static Model* FromFile(char* filePath);

		glm::vec3 color = { 1.0f, 1.0f, 1.0f };

	private:
		Shader* shader = nullptr;

		std::vector<Mesh*> allMeshes;
		std::vector<Material*> allMaterials;
	};
}
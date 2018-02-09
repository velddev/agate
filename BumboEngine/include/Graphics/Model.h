#pragma once
#include "Graphics/Transform.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/RenderSystem.h"

#include "Engine/Resources/Loadable.h"

#include <string>
#include <vector>

class Model : Loadable
{
public:
	Model();
	~Model();

	void Draw();

	Shader *GetShader();

	virtual void Load(char *filePath);

	void SetShader(Shader *shader);

	static Model *FromFile(const char *filePath);
	static Model *FromFile(char *filePath);

private:
	Shader *shader = new Shader();

	std::vector<Mesh*> allMeshes;
	std::vector<Material*> allMaterials;
};
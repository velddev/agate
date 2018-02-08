#pragma once
#include "Graphics/Transform.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"

#include <string>
#include <vector>

class Model
{
public:
	Model();
	~Model();

	Transform *transform = new Transform();

	void Draw();

	void SetShader(Shader *shader);

	static Model *FromFile(const char *filePath);
	static Model *FromFile(char *filePath);

private:
	Shader *shader = new Shader();

	std::vector<Mesh*> allMeshes;
	std::vector<Material*> allMaterials;
};
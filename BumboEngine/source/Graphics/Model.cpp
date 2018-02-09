#include "Graphics/Model.h"
#include "Graphics/Material.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Model::Model()
{
}

Model::~Model()
{
}

void Model::Draw()
{
	glm::mat4 model = glm::mat4();
	glm::mat4 model_also = transform->GetModelMatrix();

	glm::mat4 mvpMatrix = 
		glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f) * 
		glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		model_also;

	shader->Bind();

	shader->SetUniformMat4("MVP", mvpMatrix);

	for (auto x : allMeshes)
	{
		x->Draw();
	}
	shader->Unbind();
}

void Model::Load(char * filePath)
{
	const aiScene *scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (!scene)
	{
		std::cout << "err | couldn't load file '" << aiGetErrorString() << "'" << std::endl;
		return;
	}

	allMeshes.reserve(scene->mNumMeshes);

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[i];
		Mesh *newMesh = new Mesh();

		newMesh->vertices.reserve(mesh->mNumVertices);

		// Load material
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		Material *mat = new Material();

		aiColor4D diffuseColor;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);

		mat->diffuseColor = glm::vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);

		// Load vertices
		for (int j = 0; j < mesh->mNumVertices; j++)
		{
			aiVector3D vert = mesh->mVertices[j];
			aiVector3D norm = mesh->mNormals[j];

			newMesh->vertices.push_back({
				{ vert.x, vert.y, vert.z },
				{ norm.x, norm.y, norm.z }
			});
		}

		// Load indices
		newMesh->indices.reserve(mesh->mNumFaces * 3u);

		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			// Check if this face is a triangle
			assert(mesh->mFaces[j].mNumIndices == 3);

			newMesh->indices.push_back(mesh->mFaces[j].mIndices[0]);
			newMesh->indices.push_back(mesh->mFaces[j].mIndices[1]);
			newMesh->indices.push_back(mesh->mFaces[j].mIndices[2]);
		}

		newMesh->Setup();

		allMeshes.push_back(newMesh);
	}

	aiReleaseImport(scene);
}

void Model::SetShader(Shader * shader)
{
	this->shader = shader;
}

Model *Model::FromFile(const char *filePath)
{
	return FromFile((char*)filePath);
}
Model *Model::FromFile(char *filePath)
{
	Model *model = new Model();
	model->Load(filePath);
	return model;
}
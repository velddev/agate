#include "renderer/Model.h"
#include "renderer/Material.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/mat4x4.hpp>

#include <iostream>

using namespace agate::renderer;

Model::Model()
{
}

Model::~Model()
{
}

void Model::Draw()
{
	for (auto mesh : allMeshes)
	{
		mesh->Draw();
	}
}

Shader *Model::GetShader()
{
	return shader;
}

void Model::Load(char *filePath)
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
			aiVector3D uv = { 0,0,0 };

			if (mesh->HasTextureCoords(0))
			{
				uv = mesh->mTextureCoords[0][j];
			}

			newMesh->vertices.push_back({
				{ vert.x, vert.y, vert.z },
				{ norm.x, norm.y, norm.z },
				{ uv.x, uv.y }
				});
		}

		// Load indices
		newMesh->indices.reserve(long(mesh->mNumFaces * 3));

		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			// Check if this face is a triangle
			if (mesh->mFaces[j].mNumIndices == 3)
			{
				newMesh->indices.push_back(mesh->mFaces[j].mIndices[0]);
				newMesh->indices.push_back(mesh->mFaces[j].mIndices[1]);
				newMesh->indices.push_back(mesh->mFaces[j].mIndices[2]);
			}
		}

		if (newMesh->indices.size() > 0)
		{
			newMesh->Setup();
			allMeshes.push_back(newMesh);
		}
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
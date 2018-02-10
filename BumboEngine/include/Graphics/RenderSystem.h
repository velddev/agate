#pragma once
#include <glew/glew.h>

#include <vector>
#include <glm/vec3.hpp>

#include "Graphics/Lighting/PointLight.h"
#include "Graphics/Lighting/DirectionalLight.h"

class RenderObject;
class Model;

struct RenderSystemSettings {
	glm::vec3 ambientColor;
	float ambientIntensity;
};

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Add(RenderObject *model);
	
	void AddLight(PointLight *light);
	
	RenderObject *Add(Model *model);

	GLuint CreateRenderTarget();
	
	void ClearRenderTarget();

	glm::vec3 GetAmbientColor();

	float GetAmbientIntensity();

	std::vector<PointLight*> GetAllLights(glm::vec3 position);

	PointLight *GetClosestLight(glm::vec3 position);

	PointLight *GetLight(int index);
	DirectionalLight *GetDirectionalLight();

	int GetLightCount();

	RenderObject *GetRenderObject(int index);

	int GetRenderObjectCount();

	RenderSystemSettings GetSettings();

	virtual void Render();

	void UseRenderTarget(GLuint id, glm::vec2 size);
	
	void SetAmbientColor(glm::vec3 color);
	void SetAmbientIntensity(float intensity);
private:
	GLuint renderTargetId = 0;
	GLuint renderTargetTextureId = 0;

	DirectionalLight *directionalLight = new DirectionalLight();

	std::vector<PointLight*> lights;
	std::vector<RenderObject*> renderableModels;
	
	RenderSystemSettings settings;
};
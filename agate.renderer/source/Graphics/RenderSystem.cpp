#include <glew/glew.h>

#include "Graphics/Model.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/RenderObject.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Add(RenderObject *model)
{
	renderableModels.push_back(model);
}

RenderObject *RenderSystem::Add(Model *model)
{
	RenderObject *renderObject = new RenderObject(this);
	renderObject->SetModel(model);
	Add(renderObject);
	return renderObject;
}

void RenderSystem::AddLight(PointLight *light)
{
	lights.push_back(light);
}

GLuint RenderSystem::CreateRenderTarget()
{
	GLuint id;
	glGenFramebuffers(1, &id);
	return id;
}

void RenderSystem::ClearRenderTarget()
{
	renderTargetId = 0;
}

glm::vec3 RenderSystem::GetAmbientColor()
{
	return settings.ambientColor;
}

float RenderSystem::GetAmbientIntensity()
{
	return settings.ambientIntensity;
}

std::vector<PointLight*> RenderSystem::GetAllLights(glm::vec3 position)
{
	std::vector<PointLight*> lights;

	for (int i = 0; i < GetLightCount(); i++)
	{
		float dist = glm::distance(GetLight(i)->GetTransform()->GetPosition(), position);
		if (dist < GetLight(i)->GetRange())
		{
			lights.push_back(GetLight(i));
		}
	}

	return lights;
}

PointLight * RenderSystem::GetClosestLight(glm::vec3 position)
{
	float closestDistance = 9999.0f;
	int index = -1;

	for (int i = 0; i < GetLightCount(); i++)
	{
		float dist = glm::distance(GetLight(i)->GetTransform()->GetPosition(), position);
		if (dist < closestDistance)
		{
			index = i;
			closestDistance = dist;
		}
	}

	if (index == -1)
	{
		return nullptr;
	}
	return GetLight(index);
}

PointLight * RenderSystem::GetLight(int index)
{
	return lights[index];
}

DirectionalLight *RenderSystem::GetDirectionalLight()
{
	return directionalLight;
}

int RenderSystem::GetLightCount()
{
	return lights.size();
}

RenderObject * RenderSystem::GetRenderObject(int index)
{
	return renderableModels[index];
}

int RenderSystem::GetRenderObjectCount()
{
	return renderableModels.size();
}

RenderSystemSettings RenderSystem::GetSettings()
{
	return settings;
}

void RenderSystem::Render()
{
	for (auto renderable : renderableModels)
	{
		renderable->Draw();
	}
}

void RenderSystem::UseRenderTarget(GLuint id, glm::vec2 size)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	renderTargetId = id;

	if (renderTargetTextureId == 0)
	{
		glGenTextures(1, &renderTargetTextureId);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTargetTextureId, 0);

	if (renderTargetId != 0)
	{
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		return;
	}
}

void RenderSystem::SetAmbientColor(glm::vec3 color)
{
	settings.ambientColor = color;
}

void RenderSystem::SetAmbientIntensity(float intensity)
{
	settings.ambientIntensity = intensity;
}

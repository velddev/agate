#include <glew/glew.h>

#include "Graphics/RenderSystem.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Add(Model *model)
{
	renderableModels.push_back(model);
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

#pragma once
#include <glew/glew.h>
#include <stbi/stb_image.h>
#include <glm/vec2.hpp>

#include "Engine/Resources/Loadable.h"

class Texture : Loadable
{
public:
	Texture();
	~Texture();

	int GetChannelCount();
	
	GLuint GetHandle();

	glm::ivec2 GetSize();

	void Load(char *filePath);

private:
	glm::ivec2 size;
	int channelCount;
	GLuint handle;
};
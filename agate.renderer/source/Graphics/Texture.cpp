#include "Graphics/Texture.h"

Texture::Texture()
{
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
}

Texture::~Texture()
{
}

int Texture::GetChannelCount()
{
	return channelCount;
}

GLuint Texture::GetHandle()
{
	return handle;
}

glm::ivec2 Texture::GetSize()
{
	return size;
}

void Texture::Load(char *filePath)
{
	stbi_uc *texture = stbi_load(filePath, &size.x, &size.y, &channelCount, 0);

	int channelType = GL_RGBA;

	if (channelCount == 3)
	{
		channelType = GL_RGB;
	}
	else if (channelCount == 1)
	{
		channelType = GL_R8;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, channelType, size.x, size.y, 0, channelType, GL_UNSIGNED_BYTE, &texture[0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	stbi_image_free(texture);
}
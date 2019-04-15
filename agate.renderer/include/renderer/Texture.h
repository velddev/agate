#pragma once
#include <glew/glew.h>
#include <stbi/stb_image.h>
#include <glm/vec2.hpp>

#include "Engine/Resources/Loadable.h"

namespace agate::renderer
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		int GetChannelCount();

		GLuint GetHandle();

		glm::ivec2 GetSize();

		void Load(char* filePath);

		static Texture* FromFile(char* filePath);

	protected:
		glm::ivec2 size;
		int channelCount;
		GLuint handle;
	};
}
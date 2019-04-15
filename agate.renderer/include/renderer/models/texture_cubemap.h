#pragma once
#include "renderer/Texture.h"

namespace agate::renderer
{
	class TextureCubeMap : public Texture
	{
	public:
		TextureCubeMap();
		~TextureCubeMap();

		static TextureCubeMap* FromFile(char* filePath);
	};
}
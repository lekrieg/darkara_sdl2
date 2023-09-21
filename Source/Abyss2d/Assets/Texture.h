// ////////////////////////
// File: Texture.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Utils/CommonStuff.h"

#include "Asset.h"

namespace abyss2d
{
	struct Texture
	{
		SDL_Texture* data = nullptr;
		std::string fileName;
		int height = 0;
		int width = 0;
	};

	struct TextureAsset : Asset
	{
		Texture instance;
		ABYSS_INLINE TextureAsset() = default;
		ABYSS_INLINE ~TextureAsset() override
		{
			SDL_DestroyTexture(instance.data);
		}
	};
}

#endif
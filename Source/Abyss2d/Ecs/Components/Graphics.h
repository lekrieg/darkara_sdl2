// ////////////////////////
// File: Graphics.h
// Created at: 09 21, 2023
// Description:
// Modified by: Daniel Henrique
// 09 21, 2023
// ////////////////////////

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../../Assets/Asset.h"

namespace abyss2d
{
	namespace ecs
	{
		struct SpriteComponent
		{
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			assetId sprite = INVALID_ID;

			ABYSS_INLINE SpriteComponent() = default;
			ABYSS_INLINE SpriteComponent(const SpriteComponent& sc) = default;
		};
	}
}

#endif
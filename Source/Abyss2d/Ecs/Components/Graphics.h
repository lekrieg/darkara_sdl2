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

		struct TextComponent
		{
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			SDL_Color color = { 0, 0, 0, 255 };
			assetId font = INVALID_ID;
			std::string text;

			ABYSS_INLINE TextComponent(const TextComponent& tc) = default;
			ABYSS_INLINE TextComponent() = default;
		};

		struct AnimationComponent
		{
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			assetId animation = INVALID_ID;

			ABYSS_INLINE AnimationComponent() = default;
			ABYSS_INLINE AnimationComponent(const AnimationComponent& sc) = default;
		};

		struct TileMapComponent
		{
			assetId tileMap = INVALID_ID;

			ABYSS_INLINE TileMapComponent() = default;
			ABYSS_INLINE TileMapComponent(const TileMapComponent& sc) = default;
		};

		struct TileComponent
		{
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			assetId tileMap = INVALID_ID;
			assetId tileSet = INVALID_ID;
			float offset_x = 0, offset_y = 0;
			int row = 0, col = 0;

			ABYSS_INLINE TileComponent() = default;
			ABYSS_INLINE TileComponent(const TileComponent& sc) = default;
		};
	}
}

#endif
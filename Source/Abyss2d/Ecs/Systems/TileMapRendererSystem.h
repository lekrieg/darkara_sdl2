// ////////////////////////
// File: TileMapRendererSystem.h
// Created at: 09 25, 2023
// Description:
// Modified by: Daniel Henrique
// 09, 25, 2023
// ////////////////////////

#ifndef TILE_MAP_RENDERER_SYSTEM_H
#define TILE_MAP_RENDERER_SYSTEM_H

#include "../EcsSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct TileMapRendererSystem : EcsSystem
		{
		private:
			ABYSS_INLINE void DrawTile(assetId tileSetId, float x, float y, int row, int col, int size, SDL_RendererFlip flip)
			{
				SDL_FRect destinationRectangle = { x * static_cast<float>(size), y * static_cast<float>(size), static_cast<float>(size), static_cast<float>(size) };
				SDL_Rect srcRectangle = { row * size, col * size, size, size };
				auto& tileSet = _assetRegistry->Get<TextureAsset>(tileSetId)->instance;

				SDL_RenderCopyExF(_renderer, tileSet.data, &srcRectangle, &destinationRectangle, 0, nullptr, flip);

				SDL_RenderDrawRectF(_renderer, &destinationRectangle);
			}

		public:
			ABYSS_INLINE void Update(float dt) override
			{
				for(auto& e : View<TileMapComponent>())
				{
					auto& transform = e.GetComponent<TransformComponent>();
					auto& tileMap = e.GetComponent<TileMapComponent>().tileMap;

					auto& tileMapAsset = _assetRegistry->Get<TileMapAsset>(tileMap)->instance;

					for(auto& tileEnt : View<TileComponent>())
					{
						auto& tile = tileEnt.GetComponent<TileComponent>();
						if(tile.tileMap != tileMap && !tileMapAsset.tileSets.count(tile.tileSet))
						{
							continue;
						}

						float x = tile.offset_x + transform.translate.x;
						float y = tile.offset_y + transform.translate.y;

						DrawTile(tile.tileSet, x, y, tile.row, tile.col, tileMapAsset.tileSize, tile.flip);
					}
				}
			}
		};
	}
}

#endif
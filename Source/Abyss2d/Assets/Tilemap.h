// ////////////////////////
// File: Tilemap.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "../Utils/CommonStuff.h"

#include "Asset.h"

namespace abyss2d
{
	struct TileMap
	{
		std::unordered_set<assetId> tileSets;
		int columnCount = 0;
		int rowCount = 0;
		int tileSize = 0;
	};

	struct TileMapAsset : Asset
	{
		TileMap instance;
		ABYSS_INLINE TileMapAsset() = default;
	};
}

#endif
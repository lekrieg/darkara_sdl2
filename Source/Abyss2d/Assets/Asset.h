// ////////////////////////
// File: Asset.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef ASSET_H
#define ASSET_H

#include "../Utils/CommonStuff.h"

#include <cstdint>

namespace abyss2d
{
	using assetTypeId = uint32_t;
	using assetId = uuid64;

	struct Asset
	{
		assetId id = GenerateUuid();
		std::string name;
		
		ABYSS_INLINE virtual ~Asset() = default;
	};
}

#endif
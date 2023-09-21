// ////////////////////////
// File: Animation.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Utils/CommonStuff.h"

#include "Asset.h"

namespace abyss2d
{
	struct Animation
	{
		std::vector<assetId> frames;
		int speed = 100;
	};

	struct AnimationAsset : Asset
	{
		Animation instance;
		ABYSS_INLINE AnimationAsset() = default;
	};
}

#endif
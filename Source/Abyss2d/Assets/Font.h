// ////////////////////////
// File: Font.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef FONT_H
#define FONT_H

#include "../Utils/CommonStuff.h"

#include "Asset.h"

namespace abyss2d
{
	struct Font
	{
		TTF_Font* data = nullptr;
		std::string fileName;
		int size = 20;
	};

	struct FontAsset : Asset
	{
		Font instance;
		ABYSS_INLINE FontAsset() = default;
		ABYSS_INLINE ~FontAsset() override
		{
			TTF_CloseFont(instance.data);
		}
	};
}

#endif
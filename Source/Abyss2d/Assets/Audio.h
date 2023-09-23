// ////////////////////////
// File: Audio.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef AUDIO_H
#define AUDIO_H

#include "../Utils/CommonStuff.h"

#include "Asset.h"

namespace abyss2d
{
	struct AudioClip
	{
		Mix_Chunk* data = nullptr;
		std::string fileName;
	};

	struct AudioAsset : Asset
	{
		AudioClip instance;

		ABYSS_INLINE AudioAsset() = default;
		ABYSS_INLINE ~AudioAsset()
		{
			Mix_FreeChunk(instance.data);
		}
	};
}

#endif

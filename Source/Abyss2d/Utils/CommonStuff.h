// ////////////////////////
// File: CommonStuff.h
// Created at: 09 14, 2023
// Description:
// Modified by: Daniel Henrique
// 09 14, 2023
// ////////////////////////

#ifndef COMMON_STUFF_H
#define COMMON_STUFF_H

#include "../Debugging/Logger.h"

#include <set>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>
#include <memory>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <utility>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

	#ifdef ABYSS_EXPORT
		#ifdef _MSC_VER
			#define ABYSS_API __declspec(dllexport)
		#endif
	#else
		#ifdef _MSC_VER
			#define ABYSS_API __declspec(dllimport)
		#endif
	#endif

	#ifdef _MSC_VER
		#define ABYSS_INLINE __forceinline
		#define ABYSS_NO_INLINE __declspec(noinline)
	#else
		#define ABYSS_INLINE inline
		#define ABYSS_NO_INLINE
	#endif

	#define ABYSS_DELETE(p) if((p) != nullptr) { delete (p); (p) = nullptr }
	#define ABYSS_BIND(f) [this](auto&&... args) -> decltype(auto) \
		{ return this->f(std::forward<decltype(args)>(args)...); }

#define get_ticks() SDL_GetTicks() / 1000.0f
#define get_ticks_ns() SDL_GetTicks()

#define INVALID_ID 0
#define MAX_DELTA_TIME 0.05f

namespace abyss2d
{
	using uuid64 = std::size_t;

	static std::random_device randomizer;
	static std::mt19937_64 generator(randomizer());
	static std::uniform_int_distribution<uuid64> distribution;
	
	ABYSS_API ABYSS_INLINE uuid64 generate_uuid()
	{
		uuid64 uuid = INVALID_ID;
		do
		{
			uuid = distribution(generator);
		}
		while (uuid == INVALID_ID);

		return uuid;
	}
}

#endif

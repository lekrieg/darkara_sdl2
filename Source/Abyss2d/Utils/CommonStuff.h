// ////////////////////////
// File: CommonStuff.h
// Created at: 09 14, 2023
// Description:
// Modified by: Daniel Henrique
// 09 14, 2023
// ////////////////////////

#ifndef COMMON_STUFF_H
#define COMMON_STUFF_H

#include <unordered_set>
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


	// logging macros
	#if defined(_DEBUG)
		#define ABYSS_LOG(level, message, ...) \
		fprintf(stderr, "[%s] ", level); \
		fprintf(stderr, message, ##__VA_ARGS__); \
		fprintf(stderr, "\n");

		#define ABYSS_WARNING(message, ...) ABYSS_LOG("warning", message, ##__VA_ARGS__)
		#define ABYSS_ERROR(message, ...) ABYSS_LOG("error", message, ##__VA_ARGS__)
		#define ABYSS_INFO(message, ...) ABYSS_LOG("info", message, ##__VA_ARGS__)
	#else
		#define ABYSS_INFO
		#define ABYSS_ERROR	
		#define ABYSS_WARNING
	#endif

	// runtime assertion
	#define ABYSS_ASSERT assert
	// static assertion
	#define ABYSS_STATIC_ASSERT static_assert

	#ifdef _MSC_VER
		#define ABYSS_INLINE __forceinline
		#define ABYSS_NO_INLINE __declspec(noinline)
	#else
		#define ABYSS_INLINE inline
		#define ABYSS_NO_INLINE
	#endif

	#define ABYSS_DELETE(p) if((p) != nullptr) { delete (p); (p) = nullptr; }
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
	
	ABYSS_API ABYSS_INLINE uuid64 GenerateUuid()
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

// ////////////////////////
// File: Input.h
// Created at: 09 16, 2023
// Description:
// Modified by: Daniel Henrique
// 09 16, 2023
// ////////////////////////

#ifndef INPUT_H
#define INPUT_H

#include "../Utils/CommonStuff.h"

#include <vec2.hpp>

#include "Dispatcher.h"

namespace abyss2d
{
	namespace input
	{
		struct MouseState
		{
			std::bitset<7> buttons = {0};
			glm::vec2 offset;
			glm::vec2 wheel;
		};

		ABYSS_API const glm::vec2& MouseOffset();
		ABYSS_API const glm::vec2& MouseWheel();
		ABYSS_API bool IsButton(int b);
		
		ABYSS_API void Initialize(SDL_Window* w);
		ABYSS_API Dispatcher* GetDispatcher();
		ABYSS_API void DispatchEvent();
		ABYSS_API bool IsKey(int k);
	}
}

#endif

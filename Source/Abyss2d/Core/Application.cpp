#include "Application.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include <iostream>

namespace abyss2d
{
	ABYSS_API void RunApplication(const AppConfig& config)
	{
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			std::cout << "sdl initialized" << '\n';
		}

		if(IMG_Init(IMG_INIT_PNG) > 0)
		{
			std::cout << "sdl image initialized" << '\n';
		}

		if(TTF_Init() == 0)
		{
			std::cout << "sdl ttf initialized" << '\n';
		}

		if(Mix_Init(MIX_INIT_MP3) > 0)
		{
			std::cout << "sdl mixer initialized" << '\n';
		}

		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
	}
}
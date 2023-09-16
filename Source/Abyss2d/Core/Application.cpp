#include "Application.h"

namespace abyss2d
{
	ABYSS_API void RunApplication(const AppConfig& config)
	{
		Logger::Init("logging.xml");
		
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
		
		uuid64 uuid = generate_uuid();
		std::cout << uuid;
		
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();

		Logger::Destroy();
	}
}
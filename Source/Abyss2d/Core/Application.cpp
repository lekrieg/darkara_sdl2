#include "Application.h"

#include "Input.h"
#include "../Events/System.h"

namespace abyss2d
{
	static bool isRunning = true;

	ABYSS_INLINE bool OnQuit(const QuitEvent& qe)
	{
		return isRunning = false;
	}
	
	ABYSS_API void RunApplication(const AppConfig& config)
	{
		logger::Init("logging.dat");
		
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			ABYSS_ERROR(LogFlag::WriteToDebugger, "%s", "d", SDL_GetError())
			exit(EXIT_FAILURE);
		}
		
		if(IMG_Init(IMG_INIT_PNG) < 0)
		{
			ABYSS_ERROR(LogFlag::WriteToDebugger, "%s", "d", IMG_GetError())
		}
		
		if(TTF_Init() < 0)
		{
			ABYSS_ERROR(LogFlag::WriteToDebugger, "%s", "d", TTF_GetError())
		}
		
		if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512))
		{
			ABYSS_ERROR(LogFlag::WriteToDebugger, "%s", "d", Mix_GetError())
		}

		auto windowFlags = static_cast<SDL_WindowFlags>(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		SDL_Window* window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, config.width, config.height, windowFlags);
		auto rendererFlags = static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		auto renderer = SDL_CreateRenderer(window, -1, rendererFlags);
		if(!window || !renderer)
		{
			ABYSS_ERROR(LogFlag::WriteToDebugger, "%s", "s", SDL_GetError())
			exit(EXIT_FAILURE);
		}

		input::Initialize(window);
		input::GetDispatcher()->AddCallback<QuitEvent>(OnQuit);
		
		while (isRunning)
		{
			input::DispatchEvent();
			if(input::IsButton(SDL_BUTTON_LEFT))
			{
				auto mouse = input::MouseOffset();
				ABYSS_INFO(LogFlag::WriteToDebugger, "(%f %f)", "ff", mouse.x, mouse.y)
			}
			
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}

		ABYSS_INFO(LogFlag::WriteToDebugger, "this is an info!", "")
		ABYSS_ERROR(LogFlag::WriteToLogFile, "this is an error!", "")
		ABYSS_WARNING(LogFlag::WriteToDebugger, "this is a warning", "")
		
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();

		logger::Destroy();
	}
}

// ////////////////////////
// File: Application.cpp
// Created at: 09 15, 2023
// Description:
// Modified by: Daniel Henrique
// 10, 16, 2023
// ////////////////////////

#include "Application.h"

#include "Input.h"
#include "../Events/EventSystem.h"
#include "../Ecs/Scene.h"

namespace abyss2d
{
	static ecs::Scene* scene = nullptr;
	static bool isRunning = true;
	static float deltaTime, lastTick;

	ABYSS_INLINE bool OnQuit(const QuitEvent& qe)
	{
		return isRunning = false;
	}

	ABYSS_API void SetScene(ecs::Scene* s)
	{
		scene = s;
	}

	ABYSS_INLINE void ComputeDeltaTime()
	{
		deltaTime = get_ticks() - lastTick;
		if (deltaTime > MAX_DELTA_TIME)
		{
			deltaTime = MAX_DELTA_TIME;
		}
		lastTick = get_ticks();
	}

	ABYSS_API void RunApplication(const AppConfig& config)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			ABYSS_ERROR("%s", SDL_GetError())
			exit(EXIT_FAILURE);
		}

		if (IMG_Init(IMG_INIT_PNG) < 0)
		{
			ABYSS_ERROR("%s", IMG_GetError())
		}

		if (TTF_Init() < 0)
		{
			ABYSS_ERROR("%s", TTF_GetError())
		}

		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512))
		{
			ABYSS_ERROR("%s", Mix_GetError())
		}

		constexpr auto windowFlags = static_cast<SDL_WindowFlags>(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		SDL_Window* window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED,
		                                      SDL_WINDOWPOS_CENTERED, config.width, config.height, windowFlags);
		constexpr auto rendererFlags = static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);
		if (!window || !renderer)
		{
			ABYSS_ERROR("%s", SDL_GetError())
			exit(EXIT_FAILURE);
		}

		input::Initialize(window);
		input::GetDispatcher()->AddCallback<QuitEvent>(OnQuit);

		b2Vec2 gravity(0.0f, -9.8f);
		b2World world(gravity);
		int32 velocityIterations = 8;
		int32 positionIterations = 3;

		lastTick = get_ticks();

		if (!scene)
		{
			ABYSS_ERROR("%s", "No scene selected!")
			exit(EXIT_FAILURE);
		}

		scene->SetRenderer(renderer);
		scene->SetB2World(&world);
		scene->Start();

		while (isRunning)
		{
			ComputeDeltaTime();
			input::DispatchEvent();
			// if(input::IsButton(SDL_BUTTON_LEFT))
			// {
			// 	auto mouse = input::MouseOffset();
			// 	ABYSS_INFO(LogFlag::WriteToDebugger, "(%f %f)", "ff", mouse.x, mouse.y)
			// }

			SDL_RenderClear(renderer);
			world.Step(deltaTime, velocityIterations, positionIterations);
			scene->Update(deltaTime);
			SDL_RenderPresent(renderer);
		}

		// ABYSS_INFO(LogFlag::WriteToDebugger, "this is an info!", "")
		// ABYSS_ERROR(LogFlag::WriteToLogFile, "this is an error!", "")
		// ABYSS_WARNING(LogFlag::WriteToDebugger, "this is a warning", "")

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		ABYSS_DELETE(scene)
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
	}
}

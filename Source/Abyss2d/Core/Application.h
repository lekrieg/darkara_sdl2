// ////////////////////////
// File: Test.h
// Created at: 09 15, 2023
// Description:
// Modified by: Daniel Henrique
// 09 15, 2023
// ////////////////////////

#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Utils/CommonStuff.h"

namespace abyss2d::ecs
{
	struct Scene;
}

namespace abyss2d
{
	struct AppConfig
	{
		int width = 0;
		int height = 0;
		std::string title;
		std::string version;
	};

	ABYSS_API void SetScene(ecs::Scene* s);
	AppConfig CreateApplication();
	ABYSS_API void RunApplication(const AppConfig& config);
}

#endif
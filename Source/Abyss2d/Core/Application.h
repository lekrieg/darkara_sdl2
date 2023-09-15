// ////////////////////////
// File: Application.h
// Created at: 09 14, 2023
// Description:
// Modified by: Daniel Henrique
// 09 14, 2023
// ////////////////////////

#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Utils/CommonStuff.h"

#include <string>

namespace abyss2d
{
	struct AppConfig
	{
		int width = 0;
		int height = 0;
		std::string title;
		std::string version;
	};

	AppConfig CreateApplication();
	ABYSS_API void RunApplication(const AppConfig& config);
}

#endif


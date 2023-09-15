#include <Core/Entry.h>

abyss2d::AppConfig abyss2d::CreateApplication()
{
	abyss2d::AppConfig config;
	config.version = "0.0.1";
	config.title = "Test";
	config.height = 1080;
	config.width = 720;
	
	return config;
}

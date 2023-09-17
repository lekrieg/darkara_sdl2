#include <Core/Entry.h>

abyss2d::AppConfig abyss2d::CreateApplication()
{
	abyss2d::AppConfig config;
	config.version = "0.0.1";
	config.title = "Test";
	config.height = 300;
	config.width = 300;
	
	return config;
}

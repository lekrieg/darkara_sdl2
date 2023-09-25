#include <Core/Entry.h>

#include "Scenes/TestScene.h"

abyss2d::AppConfig abyss2d::CreateApplication()
{
	abyss2d::AppConfig config;
	config.version = "0.0.1";
	config.title = "Test";
	config.height = 600;
	config.width = 600;

	const auto scene = new TestScene;
	SetScene(scene);
	
	return config;
}

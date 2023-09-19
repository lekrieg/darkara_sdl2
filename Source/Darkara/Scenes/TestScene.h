// ////////////////////////
// File: TestScene.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <Ecs/Scene.h>

struct TestScene : abyss2d::ecs::Scene
{
	TestScene()
	{
		RegisterSystem<abyss2d::ecs::TestSystem>();
	}
	
	void Start() override
	{
		auto e = AddEntity("Test");
		e.AddComponent<abyss2d::ecs::TransformComponent>();

		StartSystems();
	}
};

#endif

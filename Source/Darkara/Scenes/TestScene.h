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

// #include "Assets/Animation.h"
// #include "Assets/Texture.h"
#include "Ecs/Systems/SpriteRendererSystem.h"

struct TestScene : abyss2d::ecs::Scene
{
	TestScene()
	{
		RegisterSystem<abyss2d::ecs::SpriteRendererSystem>();
	}
	
	void Start() override
	{
		// auto e = AddEntity("Test");
		// e.AddComponent<abyss2d::ecs::TransformComponent>();
		// const auto frame1 = _assetRegistry.Add<abyss2d::TextureAsset>("frame1");
		// const auto frame2 = _assetRegistry.Add<abyss2d::TextureAsset>("frame2");
		// const auto anim = _assetRegistry.Add<abyss2d::AnimationAsset>("animation test");
		//
		// anim->instance.frames.push_back(frame1->id);
		// anim->instance.frames.push_back(frame2->id);
		// anim->instance.speed = 200;
		
		auto texture = _assetRegistry.LoadTexture("Command_4x.png", "Test", abyss2d::GetRenderer());
		auto entity = AddEntity("Entity");
		entity.AddComponent<abyss2d::ecs::SpriteComponent>().sprite = texture->id;
		
		for (const auto& s : _systems)
		{
			s->Start();
		}
	}
};

#endif

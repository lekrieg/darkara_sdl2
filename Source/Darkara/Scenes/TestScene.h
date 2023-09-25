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
#include "Ecs/Systems/TextRendererSystem.h"
#include "Ecs/Systems/FrameAnimationSystem.h"

struct TestScene : abyss2d::ecs::Scene
{
	void RegisterSystems() override
	{
		RegisterSystem<abyss2d::ecs::SpriteRendererSystem>();
		RegisterSystem<abyss2d::ecs::TextRendererSystem>();
		RegisterSystem<abyss2d::ecs::FrameAnimationSystem>();
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
		
		// auto texture = _assetRegistry.LoadTexture("Command_4x.png", "Test", _renderer);
		// auto texture = _assetRegistry.LoadTexture("Assets/Command_4x.png", "Test", _renderer);
		// auto font = _assetRegistry.LoadFont("Assets/Avenixel-Regular.ttf", "ttf", 30);
		//
		// auto entity = AddEntity("Entity");
		// entity.AddComponent<abyss2d::ecs::SpriteComponent>().sprite = texture->id;
		//
		// auto entity2 = AddEntity("fontTest");
		// auto& text = entity2.AddComponent<abyss2d::ecs::TextComponent>();
		// text.text = "Hello world!";
		// text.font = font->id;

		// TODO: criar um metodo que le um sprite sheet e carrega a lista de imagens
		// TODO: arrumar forma de rodar a animacao com alguma acao
		auto frame1 = _assetRegistry.LoadTexture("Assets/Asteroids01.png", "Frame1", _renderer);
		auto frame2 = _assetRegistry.LoadTexture("Assets/Asteroids02.png", "Frame2", _renderer);
		auto frame3 = _assetRegistry.LoadTexture("Assets/Asteroids03.png", "Frame3", _renderer);

		auto animation = _assetRegistry.Add<abyss2d::AnimationAsset>("Asteroid");
		animation->instance.frames.push_back(frame1->id);
		animation->instance.frames.push_back(frame2->id);
		animation->instance.frames.push_back(frame3->id);
		animation->instance.speed = 300;

		auto entity = AddEntity("Entity");
		auto& a = entity.AddComponent<abyss2d::ecs::AnimationComponent>();
		a.animation = animation->id;
		
		for (const auto& s : _systems)
		{
			s->Start();
		}
	}
};

#endif

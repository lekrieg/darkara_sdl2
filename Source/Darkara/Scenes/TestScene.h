// ////////////////////////
// File: TestScene.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 10, 16, 2023
// ////////////////////////

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <Ecs/EcsSystem.h>

// #include "Assets/Animation.h"
// #include "Assets/Texture.h"
#include "Ecs/Systems/SpriteRendererSystem.h"
// #include "Ecs/Systems/TextRendererSystem.h"
// #include "Ecs/Systems/FrameAnimationSystem.h"
// #include "Ecs/Systems/TileMapRendererSystem.h"
#include "Ecs/Scene.h"
#include "Ecs/Systems/RigidbodySystem.h"

struct TestScene : abyss2d::ecs::Scene
{
protected:
	std::vector<abyss2d::ecs::EcsSystem*> _systems;
	abyss2d::ecs::EcsRegistry _ecsRegistry;
	abyss2d::AssetRegistry _assetRegistry;

public:
	TestScene() = default;

	~TestScene() override
	{
		for (auto& s : _systems)
		{
			ABYSS_DELETE(s)
		}

		_ecsRegistry.Clear();
		// _assetRegistry.Clear();
		_systems.clear();
	}

	ABYSS_INLINE abyss2d::ecs::Entity AddEntity(const std::string& name)
	{
		auto e = abyss2d::ecs::Entity(&_ecsRegistry);
		e.AddComponent<abyss2d::ecs::InfoComponent>().name = name;
		e.AddComponent<abyss2d::ecs::TransformComponent>();
		return e;
	}

	template <typename T>
	void RegisterSystem()
	{
		ABYSS_STATIC_ASSERT(std::is_base_of_v<abyss2d::ecs::EcsSystem, T>);
		auto newSystem = new T();
		newSystem->Prepare(&_ecsRegistry, _renderer, &_assetRegistry);
		_systems.push_back(newSystem);
	}

	void Start() override
	{
		RegisterSystem<abyss2d::ecs::SpriteRendererSystem>();
		RegisterSystem<abyss2d::ecs::RigidbodySystem>();
		// RegisterSystem<abyss2d::ecs::TextRendererSystem>();
		// RegisterSystem<abyss2d::ecs::FrameAnimationSystem>();
		// RegisterSystem<abyss2d::ecs::TileMapRendererSystem>();

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

		// ------------------------------------
		// auto frame1 = _assetRegistry.LoadTexture("Assets/Asteroids01.png", "Frame1", _renderer);
		// auto frame2 = _assetRegistry.LoadTexture("Assets/Asteroids02.png", "Frame2", _renderer);
		// auto frame3 = _assetRegistry.LoadTexture("Assets/Asteroids03.png", "Frame3", _renderer);
		//
		// auto animation = _assetRegistry.Add<abyss2d::AnimationAsset>("Asteroid");
		// animation->instance.frames.push_back(frame1->id);
		// animation->instance.frames.push_back(frame2->id);
		// animation->instance.frames.push_back(frame3->id);
		// animation->instance.speed = 300;
		//
		// auto entity = AddEntity("Entity");
		// auto& a = entity.AddComponent<abyss2d::ecs::AnimationComponent>();
		// a.animation = animation->id;
		// ------------------------------------

		// auto tsTexture = _assetRegistry.LoadTexture("Assets/SpaceCaveTileset.png", "", _renderer);
		//
		// auto tileMap = _assetRegistry.Add<abyss2d::TileMapAsset>("TileMapAsset");
		// tileMap->instance.tileSets.insert(tsTexture->id);
		// tileMap->instance.columnCount = 12;
		// tileMap->instance.rowCount = 11;
		// tileMap->instance.tileSize = 16;
		//
		// AddEntity("TileMap").AddComponent<abyss2d::ecs::TileMapComponent>().tileMap = tileMap->id;
		//
		// for (int column = 0; column < tileMap->instance.columnCount; column++)
		// {
		// 	for (int row = 0; row < tileMap->instance.rowCount; row++)
		// 	{
		// 		auto e = AddEntity("tile");
		// 		auto& tile = e.AddComponent<abyss2d::ecs::TileComponent>();
		// 		tile.tileSet = tsTexture->id;
		// 		tile.tileMap = tileMap->id;
		// 		tile.offset_x = column;
		// 		tile.offset_y = row;
		// 		tile.row = column;
		// 		tile.col = row;
		// 	}
		// }

		auto sprite = _assetRegistry.LoadTexture("Assets/LifeIcon.png", "", _renderer);

		auto e = AddEntity("Rigidbody");
		e.AddComponent<abyss2d::ecs::SpriteComponent>().sprite = sprite->id;
		auto& rb = e.AddComponent<abyss2d::ecs::RigidbodyComponent>();
		rb.boundingBoxEnabled = true;

		for (const auto& s : _systems)
		{
			s->Start();
		}
	}

	void Update(const float dt) override
	{
		// SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		for (auto& s : _systems)
		{
			s->Update(dt);
		}

		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		for (auto& e : _ecsRegistry.View<abyss2d::ecs::RigidbodyComponent>())
		{
			auto& rb = _ecsRegistry.GetComponent<abyss2d::ecs::RigidbodyComponent>(e);
			SDL_RenderDrawRectF(_renderer, &rb.boundingBox);
		}
		SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	}
};

#endif

//--
// TODO: criar um metodo que le um sprite sheet e carrega a lista de imagens
//--
// TODO: arrumar forma de rodar a animacao com alguma acao
//--
// TODO: melhorar o sistema de tiles - talvez fazer tile batching, clipping space ou tile buffering
//--
// TODO: melhorar a fisica
// https://www.iforce2d.net/b2dtut/constant-speed
// https://forum.processing.org/two/discussion/8513/how-do-i-get-a-body-s-velocity-in-box2d.html
//--

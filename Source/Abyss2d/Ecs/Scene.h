// ////////////////////////
// File: Scene.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef SCENE_H
#define SCENE_H

#include "EcsSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct Scene
		{
		protected:
			std::vector<ecs::EcsSystem*> _systems;
			SDL_Renderer* _renderer = nullptr;
			EcsRegistry _ecsRegistry;
			AssetRegistry _assetRegistry;

		public:
			virtual ~Scene()
			{
				for(auto& s : _systems)
				{
					ABYSS_DELETE(s)
				}

				_ecsRegistry.Clear();
				// _assetRegistry.Clear();
				_systems.clear();
			}
			
			ABYSS_INLINE void SetRenderer(SDL_Renderer* renderer)
			{
				_renderer = renderer;
			}

			ABYSS_INLINE ecs::Entity AddEntity(const std::string& name)
			{
				auto e = ecs::Entity(&_ecsRegistry);
				e.AddComponent<InfoComponent>().name = name;
				e.AddComponent<TransformComponent>();
				return e;
			}

			ABYSS_INLINE void Update(const float dt)
			{
				// SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
				for(auto& s : _systems)
				{
					s->Update(dt);
				}
			}

			virtual void RegisterSystems() = 0;
			
			template <typename T>
			void RegisterSystem()
			{
				ABYSS_STATIC_ASSERT(std::is_base_of_v<ecs::EcsSystem, T>);
				auto newSystem = new T();
				newSystem->Prepare(&_ecsRegistry, _renderer, &_assetRegistry);
				_systems.push_back(newSystem);
			}

			virtual void Start() = 0;
		};
	}
}

#endif
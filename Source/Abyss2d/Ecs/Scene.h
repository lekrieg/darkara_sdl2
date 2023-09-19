// ////////////////////////
// File: Scene.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 09 19, 2023
// ////////////////////////

#ifndef SCENE_H
#define SCENE_H

#include "Systems/TestSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct Scene
		{
		private:
			std::vector<ecs::EcsSystem*> _systems;
			SDL_Renderer* _renderer = nullptr;
			ecs::registry _registry;

		public:
			virtual ~Scene()
			{
				for(auto& s : _systems)
				{
					ABYSS_DELETE(s)
				}

				_registry.Clear();
				_systems.clear();
			}
			
			ABYSS_INLINE void SetRenderer(SDL_Renderer* renderer)
			{
				_renderer = renderer;
			}

			ABYSS_API ABYSS_INLINE ecs::Entity AddEntity(const std::string& name)
			{
				auto e = ecs::Entity(&_registry);
				e.AddComponent<InfoComponent>().name = name;
				e.AddComponent<TransformComponent>();
				return e;
			}

			ABYSS_API ABYSS_INLINE void StartSystems() const
			{
				for (const auto& s : _systems)
				{
					s->Start();
				}
			}

			ABYSS_INLINE void Update(const float dt)
			{
				for(auto& s : _systems)
				{
					s->Update(dt);
				}
			}

			template <typename T>
			void RegisterSystem()
			{
				ABYSS_STATIC_ASSERT(std::is_base_of_v<ecs::EcsSystem, T>);
				auto newSystem = new T();
				newSystem->Prepare(&_registry, _renderer);
				_systems.push_back(newSystem);
			}

			virtual void Start() = 0;
		};
	}
}

#endif
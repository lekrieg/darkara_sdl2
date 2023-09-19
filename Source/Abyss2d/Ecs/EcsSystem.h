// ////////////////////////
// File: EcsSystem.h
// Created at: 09 17, 2023
// Description:
// Modified by: Daniel Henrique
// 09 17, 2023
// ////////////////////////

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "Entity.h"

namespace abyss2d
{
	namespace ecs
	{
		struct EcsSystem
		{
		protected:
			SDL_Renderer* _renderer = nullptr;
			registry* _registry = nullptr;

		public:
			ABYSS_INLINE virtual ~EcsSystem() = default;
			ABYSS_INLINE void Prepare(registry* rg, SDL_Renderer* rd)
			{
				_registry = rg;
				_renderer = rd;
			}

			template<typename T>
			ABYSS_INLINE auto View()
			{
				std::vector<Entity> entities;
				for(auto& e : _registry->View<T>())
				{
					entities.push_back(Entity{ e, _registry });
				}

				return entities;
			}

			ABYSS_INLINE virtual void Update(float) {}
			ABYSS_INLINE virtual void Start() {}
		};
	}
}

#endif
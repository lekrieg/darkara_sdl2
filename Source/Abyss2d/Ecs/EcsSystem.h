﻿// ////////////////////////
// File: EcsSystem.h
// Created at: 09 17, 2023
// Description:
// Modified by: Daniel Henrique
// 09 17, 2023
// ////////////////////////

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "Entity.h"
#include "../Assets/AssetRegistry.h"

namespace abyss2d
{
	namespace ecs
	{
		struct EcsSystem
		{
		protected:
			SDL_Renderer* _renderer = nullptr;
			EcsRegistry* _ecsRegistry = nullptr;
			AssetRegistry* _assetRegistry = nullptr;

		public:
			ABYSS_INLINE virtual ~EcsSystem() = default;
			ABYSS_INLINE void Prepare(EcsRegistry* rg, SDL_Renderer* rd, AssetRegistry* asr)
			{
				_ecsRegistry = rg;
				_renderer = rd;
				_assetRegistry = asr;
			}

			template<typename T>
			ABYSS_INLINE auto View()
			{
				std::vector<Entity> entities;
				for(auto& e : _ecsRegistry->View<T>())
				{
					entities.push_back(Entity{ e, _ecsRegistry });
				}

				return entities;
			}

			ABYSS_INLINE virtual void Update(float) {}
			ABYSS_INLINE virtual void Start() {}
		};
	}
}

#endif
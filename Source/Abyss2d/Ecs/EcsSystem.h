// ////////////////////////
// File: EcsSystem.h
// Created at: 09 17, 2023
// Description:
// Modified by: Daniel Henrique
// 10, 12, 2023
// ////////////////////////

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "Entity.h"
#include "../Assets/AssetRegistry.h"
#include "Components/Common.h"
#include "Components/Graphics.h"
#include "Components/Physics.h"

namespace abyss2d::ecs
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

		template <typename T>
		ABYSS_INLINE auto View()
		{
			std::vector<Entity> entities;
			for (auto& e : _ecsRegistry->View<T>())
			{
				entities.push_back(Entity(e, _ecsRegistry));
			}
			return entities;
		}

		ABYSS_INLINE virtual void Update(float dt)
		{
		}

		ABYSS_INLINE virtual void Start()
		{
		}
	};
}

#endif

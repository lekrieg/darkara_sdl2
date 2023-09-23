// ////////////////////////
// File: SpriteRendererSystem.h
// Created at: 09 21, 2023
// Description:
// Modified by: Daniel Henrique
// 09 21, 2023
// ////////////////////////

#ifndef SPRITE_RENDERER_SYSTEM_H
#define SPRITE_RENDERER_SYSTEM_H

#include "../EcsSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct SpriteRendererSystem : EcsSystem
		{
			void Update(float dt) override
			{
				for (auto& e : View<SpriteComponent>())
				{
					auto& transform = e.GetComponent<TransformComponent>();
					auto& sComponent = e.GetComponent<SpriteComponent>();

					auto& texture = _assetRegistry->Get<TextureAsset>(sComponent.sprite)->instance;
					
					SDL_FRect destinationRectangle
					{
						transform.translate.x, transform.translate.y,
						texture.width * transform.scale.x, texture.height * transform.scale.y
					};
					
					SDL_RenderCopyExF(_renderer, texture.data, nullptr, &destinationRectangle,
						transform.rotation, nullptr, sComponent.flip);
				}
			}
		};
	}
}

#endif
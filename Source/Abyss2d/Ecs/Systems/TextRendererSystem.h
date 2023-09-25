// ////////////////////////
// File: TextRendererSystem.h
// Created at: 09 24, 2023
// Description:
// Modified by: Daniel Henrique
// 09 24, 2023
// ////////////////////////

#ifndef TEXT_RENDERER_SYSTEM_H
#define TEXT_RENDERER_SYSTEM_H

#include "../EcsSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct TextRendererSystem : EcsSystem
		{
			ABYSS_INLINE void Update(float dt) override
			{
				for (auto& e : View<TextComponent>())
				{
					auto& transform = e.GetComponent<TransformComponent>();
					auto& text = e.GetComponent<TextComponent>();

					auto& font = _assetRegistry->Get<FontAsset>(text.font)->instance;

					SDL_Surface* surface = TTF_RenderText_Blended(font.data, text.text.c_str(),
						text.color);
					if(!surface)
					{
						ABYSS_ERROR("%s", TTF_GetError())
						continue;
					}

					SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
					SDL_FreeSurface(surface);
					if(!texture)
					{
						ABYSS_ERROR("%s", SDL_GetError())
						continue;
					}

					int w, h;
					SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

					SDL_FRect destinationRectangle
					{
						transform.translate.x, transform.translate.y,
						w * transform.scale.x, h * transform.scale.y
					};

					SDL_RenderCopyExF(_renderer, texture, nullptr, &destinationRectangle,
						transform.rotation, nullptr, text.flip);

					SDL_DestroyTexture(texture);
				}
			}
		};
	}
}

#endif
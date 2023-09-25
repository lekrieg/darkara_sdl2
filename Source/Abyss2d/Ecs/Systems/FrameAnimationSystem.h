// ////////////////////////
// File: FrameAnimationSystem.h
// Created at: 09 25, 2023
// Description:
// Modified by: Daniel Henrique
// 09 25, 2023
// ////////////////////////

#ifndef FRAME_ANIMATION_SYSTEM_H
#define FRAME_ANIMATION_SYSTEM_H

#include "../EcsSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct FrameAnimationSystem : EcsSystem
		{
			void Update(float dt) override
			{
				for (auto& e : View<AnimationComponent>())
				{
					auto& transform = e.GetComponent<TransformComponent>();
					auto& aComponent = e.GetComponent<AnimationComponent>();

					auto& anim = _assetRegistry->Get<AnimationAsset>(aComponent.animation)->instance;

					int index = (get_ticks_ns() / anim.speed) % anim.frames.size();
					auto& frame = _assetRegistry->Get<TextureAsset>(anim.frames[index])->instance;
					
					SDL_FRect destinationRectangle
					{
						transform.translate.x, transform.translate.y,
						frame.width * transform.scale.x, frame.height * transform.scale.y
					};
					
					SDL_RenderCopyExF(_renderer, frame.data, nullptr, &destinationRectangle,
						transform.rotation, nullptr, aComponent.flip);
				}
			}
		};
	}
}

#endif

// ////////////////////////
// File: Scene.h
// Created at: 09 19, 2023
// Description:
// Modified by: Daniel Henrique
// 10, 16, 2023
// ////////////////////////

#ifndef SCENE_H
#define SCENE_H

namespace abyss2d::ecs
{
	struct Scene
	{
	protected:
		SDL_Renderer* _renderer = nullptr;
		b2World* _b2World;

	public:
		Scene() = default;
		virtual ~Scene() = default;

		ABYSS_INLINE virtual void Update(const float dt) = 0;
		ABYSS_INLINE virtual void Start() = 0;

		ABYSS_INLINE void SetRenderer(SDL_Renderer* renderer)
		{
			_renderer = renderer;
		}

		ABYSS_INLINE void SetB2World(b2World* bW)
		{
			_b2World = bW;
		}
	};
}

#endif

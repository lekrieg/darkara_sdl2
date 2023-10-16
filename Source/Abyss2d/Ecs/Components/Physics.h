// ////////////////////////
// File: Physics.h
// Created at: 10 12, 2023
// Description:
// Modified by: Daniel Henrique
// 10, 12, 2023
// ////////////////////////

#ifndef PHYSICS_H
#define PHYSICS_H

#include "../../Assets/Asset.h"

namespace abyss2d::ecs
{
	struct RigidbodyComponent
	{
		bool boundingBoxEnabled = false;
		SDL_FRect boundingBox = {0.0f, 0.0f, 64.0f, 64.0f};

		ABYSS_INLINE RigidbodyComponent() = default;
		ABYSS_INLINE RigidbodyComponent(const RigidbodyComponent& rb) = default;
	};
}

#endif

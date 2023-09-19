// ////////////////////////
// File: Common.h
// Created at: 09 18, 2023
// Description:
// Modified by: Daniel Henrique
// 09 18, 2023
// ////////////////////////

#ifndef COMMON_H
#define COMMON_H

#include "../../Utils/CommonStuff.h"

#include <vec2.hpp>

namespace abyss2d
{
	namespace ecs
	{
		struct InfoComponent
		{
			uuid64 uuid = GenerateUuid();
			std::string name = "entity";
			std::string tag = "default";

			ABYSS_INLINE InfoComponent(const InfoComponent& ic) = default;
			ABYSS_INLINE InfoComponent() = default;
		};

		struct TransformComponent
		{
			glm::vec2 translate = glm::vec2(0.0f, 0.0f);
			glm::vec2 scale = glm::vec2(1.0f);
			float rotation = 0.0f;

			ABYSS_INLINE TransformComponent(const TransformComponent& ic) = default;
			ABYSS_INLINE TransformComponent() = default;
		};
	}
}

#endif
// ////////////////////////
// File: TestSystem.h
// Created at: 09 18, 2023
// Description:
// Modified by: Daniel Henrique
// 09 18, 2023
// ////////////////////////

#ifndef TEST_SYSTEM_H
#define TEST_SYSTEM_H

#include "../EcsSystem.h"

namespace abyss2d
{
	namespace ecs
	{
		struct TestSystem : EcsSystem
		{
			void Update(float dt) override
			{
				for (auto e : View<TransformComponent>())
				{
					auto &t = e.GetComponent<TransformComponent>();
					ABYSS_INFO("id[%llu]: x: %f", e.Id(), t.translate.x++);
				}
			}
		};
	}
}

#endif

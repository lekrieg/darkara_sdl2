// ////////////////////////
// File: RigidbodySystem.h
// Created at: 10 12, 2023
// Description:
// Modified by: Daniel Henrique
// 10, 12, 2023
// ////////////////////////

#ifndef RIGIDBODY_SYSTEM_H
#define RIGIDBODY_SYSTEM_H

#include "../EcsSystem.h"

namespace abyss2d::ecs
{
	struct RigidbodySystem : EcsSystem
	{
		void Start() override
		{
			for (auto& e : View<RigidbodyComponent>())
			{
				auto& transform = e.GetComponent<TransformComponent>();
				auto& rb = e.GetComponent<RigidbodyComponent>();

				rb.boundingBox.x = transform.translate.x;
				rb.boundingBox.y = transform.translate.y;
			}
		}

		void Update(float dt) override
		{
			for (auto& e : View<RigidbodyComponent>())
			{
				auto& transform = e.GetComponent<TransformComponent>();
				auto& rb = e.GetComponent<RigidbodyComponent>();

				if (rb.boundingBoxEnabled)
				{
					rb.boundingBox.x = transform.translate.x;
					rb.boundingBox.y = transform.translate.y;
				}
			}
		}
	};
}
#endif

// ////////////////////////
// File: Entity.h
// Created at: 09 17, 2023
// Description:
// Modified by: Daniel Henrique
// 09 17, 2023
// ////////////////////////

#ifndef ENTITY_H
#define ENTITY_H

#include "EcsRegistry.h"

namespace abyss2d
{
	namespace ecs
	{
		struct Entity
		{
		private:
			entityId _entity = INVALID_ID;
			EcsRegistry* _registry = nullptr;

		public:
			ABYSS_INLINE Entity(EcsRegistry* r): _registry(r) { _entity = r->AddEntity(); }
			ABYSS_INLINE Entity(entityId e, EcsRegistry* r): _entity(e), _registry(r) { }
			ABYSS_INLINE Entity() = default;
			ABYSS_INLINE operator entityId() { return _entity; }

			template<typename T, typename... Args>
			ABYSS_INLINE T& AddComponent(Args&&... args)
			{
				return _registry->AddComponent<T>(_entity, std::forward<Args>(args)...);
			}

			template<typename T>
			ABYSS_INLINE T& GetComponent()
			{
				return _registry->GetComponent<T>(_entity);
			}

			template<typename T>
			ABYSS_INLINE T& RemoveComponent()
			{
				return _registry->RemoveComponent<T>(_entity);
			}
			
			template<typename T>
			ABYSS_INLINE T& HasComponent()
			{
				return _registry->HasComponent<T>(_entity);
			}

			ABYSS_INLINE bool IsAlive()
			{
				return _registry && _registry->IsAlive(_entity);
			}

			ABYSS_INLINE entityId Id()
			{
				return _entity;
			}

			ABYSS_INLINE void Destroy()
			{
				_registry->Destroy(_entity);
			}
		};
	}
}

#endif

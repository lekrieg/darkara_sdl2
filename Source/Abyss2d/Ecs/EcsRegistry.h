// ////////////////////////
// File: EcsRegistry.h
// Created at: 09 17, 2023
// Description:
// Modified by: Daniel Henrique
// 09 17, 2023
// ////////////////////////

#ifndef ECS_REGISTRY_H
#define ECS_REGISTRY_H

#include "Ecs.h"

namespace abyss2d::ecs
{
	struct EcsRegistry
	{
	private:
		std::unordered_map<componentId, ArrayInstance*> _components;
		std::unordered_map<entityId, signature> _signatures;
		entityId _nextId = INVALID_ID;

	public:
		ABYSS_INLINE void Clear()
		{
			for (auto& [_, a] : _components)
			{
				ABYSS_DELETE(a)
			}
			
      		_components.clear();
      		_signatures.clear();
      		_nextId = INVALID_ID;
		}

		ABYSS_INLINE entityId AddEntity()
		{
			entityId entity = (++_nextId);
			_signatures[entity] = signature();
			return entity;
		}

		ABYSS_INLINE void Destroy(entityId e)
		{
			for (auto& [_, a] : _components)
			{
				a->Erase(e);
			}
			_signatures.erase(e);
		}

		ABYSS_INLINE bool IsAlive(entityId e)
		{
			return _signatures.count(e);
		}

		template <typename T>
		ABYSS_INLINE entityList View()
		{
			entityList list;
			for (auto& [entity, sig] : _signatures)
			{
				if (sig.count(TypeId<T>()))
				{
					list.insert(entity);
					continue;
				}
			}
			return list;
		}

		template <typename T>
		ABYSS_INLINE ComponentArray<T>* GetComponentArray()
		{
			componentId type = TypeId<T>();
			if (_components.count(type))
			{
				return static_cast<ComponentArray<T>*>(_components.at(type));
			}
			auto array = new ComponentArray<T>();
			_components[type] = array;
			return array;
		}

		template <typename T>
		ABYSS_INLINE T& GetComponent(entityId e)
		{
			ABYSS_ASSERT(_signatures.count(e) && "Out of range!");
			return GetComponentArray<T>()->Get(e);
		}

		template <typename T, typename... Args>
		ABYSS_INLINE T& AddComponent(entityId e, Args&&... args)
		{
			ABYSS_ASSERT(_signatures.count(e) && "Out of range!");
			auto data = T(std::forward<Args>(args)...);
			_signatures[e].insert(TypeId<T>());
			return GetComponentArray<T>()->Push(e, data);
		}

		template <typename T>
		ABYSS_INLINE void RemoveComponent(entityId e)
		{
			_signatures.at(e).erase(TypeId<T>());
			GetComponentArray<T>()->erase(e);
		}

		template <typename T>
		ABYSS_INLINE bool HasComponent(entityId e)
		{
			return _signatures.count(e) && _signatures.at(e).count(TypeId<T>());
		}
	};
}

#endif

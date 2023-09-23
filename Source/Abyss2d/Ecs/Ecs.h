// ////////////////////////
// File: Ecs.h
// Created at: 09 17, 2023
// Description:
// Modified by: Daniel Henrique
// 09 17, 2023
// ////////////////////////

#ifndef ECS_H
#define ECS_H

#include "../core/typeid.h"

namespace abyss2d
{
	namespace ecs
	{
		using entityId = size_t;
		using componentId = uint32_t;
		using signature = std::unordered_set<uint32_t>;
		using entityList = std::unordered_set<entityId>;

		struct ArrayInstance
		{
			ABYSS_INLINE virtual ~ArrayInstance() = default;
			virtual void Erase(entityId) = 0;
		};
		
		template<typename T>
		struct ArrayEntry
		{
			ABYSS_INLINE ArrayEntry(entityId e, const T& d): entity(e), data(d) {}
			ABYSS_INLINE operator entityId() const { return entity; }
			entityId entity = INVALID_ID;
			T data;
		};

		template<typename T>
		struct ComponentArray : ArrayInstance
		{
		private:		
			std::vector<ArrayEntry<T>> _data;

		public:
			ABYSS_INLINE T& Push(entityId e, const T& data)
			{
				if (Exits(e)) { return Get(e); }
				_data.push_back(ArrayEntry(e, data));
				return _data.back().data;			
			}

			ABYSS_INLINE void Erase(entityId e) override
			{	
				auto it = std::find(_data.begin(), _data.end(), e);
				if (it != _data.end()) { _data.erase(it); }
			}	

			ABYSS_INLINE bool Exits(entityId e)
			{	
				return std::find(_data.begin(), _data.end(), e) != _data.end();
			}

			ABYSS_INLINE T& Get(entityId e)
			{
				ABYSS_ASSERT(Exits(e) && "Entity out of range!");
				return (*std::find(_data.begin(), _data.end(), e)).data;
			}
		};
	}
}
	
#endif
// ////////////////////////
// File: Dispatcher.h
// Created at: 09 16, 2023
// Description:
// Modified by: Daniel Henrique
// 09 16, 2023
// ////////////////////////

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Event.h"

namespace abyss2d
{
	struct Dispatcher
	{
	private:
		std::unordered_map<EventId, EventInstance*> _events;
		std::unordered_map<EventId, CallbackList> _callbacks;

	public:
		template<typename T, typename... Args>
		ABYSS_INLINE void Post(Args&&... args)
		{
			ABYSS_ASSERT((std::is_base_of_v<EventInstance, T>));
			_events[TypeId<T>()] = new T(std::forward<Args>(args)...);
		}

		template<typename T>
		ABYSS_INLINE void AddCallback(CallbackFunction<T>&& c)
		{
			ABYSS_ASSERT((std::is_base_of_v<EventInstance, T>));
			auto entry = std::make_shared<EventCallback<T>>(c);
			_callbacks[TypeId<T>()].push_back(entry);
		}

		ABYSS_INLINE void Dispatch()
		{
			if(_events.empty()) { return; }
			for(auto &[code, entry] : _events)
			{
				for(const auto& c : _callbacks[code])
				{
					if(c->Run(entry)) { break; }
				}
			}

			_events.clear();
		}
	};
}

#endif
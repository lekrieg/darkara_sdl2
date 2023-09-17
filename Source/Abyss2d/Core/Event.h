// ////////////////////////
// File: Event.h
// Created at: 09 16, 2023
// Description:
// Modified by: Daniel Henrique
// 09 16, 2023
// ////////////////////////

#ifndef EVENT_H
#define EVENT_H

#include "TypeId.h"

namespace abyss2d
{
	using EventId = uint32_t;

	struct EventInstance
	{
		ABYSS_INLINE virtual ~EventInstance() = default;
	};

	template<typename T>
	using CallbackFunction = std::function<bool(const T& t)>;

	struct CallbackInstance
	{
		ABYSS_INLINE virtual ~CallbackInstance() = default;
		virtual bool Run(EventInstance* ei) = 0;
	};

	template<typename T>
	struct EventCallback : CallbackInstance
	{
	private:
		CallbackFunction<T> callback;

	public:
		ABYSS_INLINE EventCallback(CallbackFunction<T>& c) : callback(c) {}

		ABYSS_INLINE bool Run(EventInstance* ei) override
		{
			auto data = static_cast<const T&>(*ei);
			return callback(data);
		}
	};

	using CallbackList = std::vector<std::shared_ptr<CallbackInstance>>;
}

#endif

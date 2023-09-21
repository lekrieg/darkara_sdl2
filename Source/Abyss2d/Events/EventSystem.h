// ////////////////////////
// File: System.h
// Created at: 09 16, 2023
// Description:
// Modified by: Daniel Henrique
// 09 16, 2023
// ////////////////////////

#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "../Core/Event.h"

namespace abyss2d
{
	struct QuitEvent : EventInstance
	{
		ABYSS_INLINE QuitEvent() = default;
	};

	struct KeyDownEvent : EventInstance
	{
		ABYSS_INLINE KeyDownEvent(int key) : key(key) {}
		int key;
	};

	struct KeyUpEvent : EventInstance
	{
		ABYSS_INLINE KeyUpEvent(int key) : key(key) {}
		int key;
	};

	struct KeyRepeatEvent : EventInstance
	{
		ABYSS_INLINE KeyRepeatEvent(int key) : key(key) {}
		int key;
	};

	struct MouseDownEvent : EventInstance
	{
		ABYSS_INLINE MouseDownEvent(int btn):button(btn) {}
		int button;
	};

	struct MouseUpEvent : EventInstance
	{
		ABYSS_INLINE MouseUpEvent(int btn) : button(btn) {}
		int button;
	};

	struct MouseMotionEvent : EventInstance
	{
		ABYSS_INLINE MouseMotionEvent() = default;
	};

	struct MouseWheelEvent : EventInstance
	{
		ABYSS_INLINE MouseWheelEvent() = default;
	};
}

#endif
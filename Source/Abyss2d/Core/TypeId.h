// ////////////////////////
// File: TypeId.h
// Created at: 09 16, 2023
// Description:
// Modified by: Daniel Henrique
// 09 16, 2023
// ////////////////////////

#ifndef TYPE_ID_H
#define TYPE_ID_H

#include "../Utils/CommonStuff.h"

namespace abyss2d
{
	ABYSS_INLINE uint32_t GetUniqueTypeId()
	{
		static uint32_t type = 1u;
		return type++;
	}

	template<typename T>
	ABYSS_INLINE uint32_t TypeId()
	{
		static const uint32_t type = GetUniqueTypeId();
		return type;
	}
}

#endif
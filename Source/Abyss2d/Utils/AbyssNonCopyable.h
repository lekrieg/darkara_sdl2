// ////////////////////////
// File: AbyssNonCopyable.h
// Created at: 09 15, 2023
// Description:
// Modified by: Daniel Henrique
// 09 15, 2023
// ////////////////////////

#ifndef ABYSS_NON_COPYABLE_H
#define ABYSS_NON_COPYABLE_H

class AbyssNonCopyable
{
public:
	AbyssNonCopyable(const AbyssNonCopyable& x) = delete;
	AbyssNonCopyable& operator=(const AbyssNonCopyable& x) = delete;
	
	AbyssNonCopyable() = default;
	AbyssNonCopyable(AbyssNonCopyable&& x) = default;
	AbyssNonCopyable& operator=(AbyssNonCopyable&& x) = default;
	
	~AbyssNonCopyable() = default;
};

#endif
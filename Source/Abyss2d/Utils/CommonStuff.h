// ////////////////////////
// File: CommonStuff.h
// Created at: 09 14, 2023
// Description:
// Modified by: Daniel Henrique
// 09 14, 2023
// ////////////////////////

#ifndef COMMON_STUFF_H
#define COMMON_STUFF_H

	#ifdef ABYSS_EXPORT
		#ifdef _MSC_VER
			#define ABYSS_API __declspec(dllexport)
		#endif
	#else
		#ifdef _MSC_VER
			#define ABYSS_API __declspec(dllimport)
		#endif
	#endif

#endif

// ////////////////////////
// File: Entry.h
// Created at: 09 14, 2023
// Description:
// Modified by: Daniel Henrique
// 09 14, 2023
// ////////////////////////

#ifndef ENTRY_H
#define ENTRY_H

#include "Application.h"

extern abyss2d::AppConfig abyss2d::CreateApplication();

int main(int argc, char** argv)
{
	auto config = abyss2d::CreateApplication();
	abyss2d::RunApplication(config);

	return 0;
}

#endif

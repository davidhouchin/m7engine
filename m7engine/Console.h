/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/*
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

#include "Font.h"
#include "InputManager.h"
#include "Primitives.h"

namespace M7engine
{
class Console
{
public:
	Console();
	virtual ~Console();

	void update();
	void draw();

private:
	Font *consoleFont;

	ALLEGRO_COLOR systemColor, defaultColor, errorColor, infoColor;

	bool consoleOpened = false, cursorFlash = true, cursorIsFlashing = false;

	int cursorInterval = 20, cursorTimer = 0, cursorPosition = 0, cursorX = 0, cursorY = 0,
		consoleScroll = 0, consoleKeyStop = 0, consoleKeytimer = 0, consoleKeyTime = 0,
		consoleHistoryCount = 10, consoleHistoryCurrent = 0, consoleLines = 5;

	float consoleAlpha = 0.6, consoleKeyStopTime = 0.6, consoleKeyRepeatTime = 0.3;

	std::string consolePrompt = ">>>", consoleText = "", consoleHistory[10];

	std::vector<ALLEGRO_COLOR> consoleLineColor;
	std::vector<std::string> consoleLineText;
};
};

#endif*/
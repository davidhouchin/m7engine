/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/*
#include "Console.h"

namespace M7engine
{
	Console::Console()
	{
		for (int i = 1; i <= consoleHistoryCount; ++i)
		{
			consoleHistory[i] = "";
		}
		for (int i = 1; i <= consoleLines; ++i)
		{
			consoleLineColor[i] = defaultColor;
			consoleLineText[i] = "";
		}
	}
	
	void Console::update()
	{
		if (InputManager::getInstance()->getKeyReleased(ALLEGRO_KEY_TILDE) && consoleOpened)
		{
			consoleOpened = false;
			consoleHistoryCurrent = 0;
			consoleText = "";
		}

		if (InputManager::getInstance()->getKeyReleased(ALLEGRO_KEY_TILDE) &&
			InputManager::getInstance()->getKeyHeld(ALLEGRO_KEYMOD_SHIFT))
		{
			consoleOpened = true;
		}

		if (cursorFlash)
		{
			cursorTimer++;
			if (cursorTimer >= cursorInterval)
			{
				cursorIsFlashing = !cursorIsFlashing;
				cursorTimer = 0;
			}
		}

		if (consoleOpened)
		{
		}
	}
}*/
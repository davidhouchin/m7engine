/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

/*
          _____                   _______                   _____                    _____            ____
         /\    \                 /::\    \                 /\    \                  /\    \          /\   \
        /::\____\               /::::\    \               /::\    \                /::\    \        /::\   \
       /::::|   |              /::::::\    \             /::::\    \              /::::\    \       \:::\   \
      /:::::|   |             /::::::::\    \           /::::::\    \            /::::::\    \       \:::\   \
     /::::::|   |            /:::/--\:::\    \         /:::/\:::\    \          /:::/\:::\    \       \:::\   \
    /:::/|::|   |           /:::/    \:::\    \       /:::/  \:::\    \        /:::/__\:::\    \       \:::\   \
   /:::/ |::|   |          /:::/    / \:::\    \     /:::/    \:::\    \      /::::\   \:::\    \       \:::\   \
  /:::/  |::|___|______   /:::/____/   \:::\____\   /:::/    / \:::\    \    /::::::\   \:::\    \       \:::\   \
 /:::/   |::::::::\    \ |:::|    |     |:::|    | /:::/    /   \:::\ ___\  /:::/\:::\   \:::\    \       \:::\   \
/:::/    |:::::::::\____\|:::|____|     |:::|    |/:::/____/     \:::|    |/:::/__\:::\   \:::\____\       \:::\___\
\::/    / -----/:::/    / \:::\    \   /:::/    / \:::\    \     /:::|____|\:::\   \:::\   \::/    /       /:::/   /
 \/____/      /:::/    /   \:::\    \ /:::/    /   \:::\    \   /:::/    /  \:::\   \:::\   \/____/       /:::/   /
             /:::/    /     \:::\    /:::/    /     \:::\    \ /:::/    /    \:::\   \:::\    \          /:::/   /
            /:::/    /       \:::\__/:::/    /       \:::\    /:::/    /      \:::\   \:::\____\        /:::/   /
           /:::/    /         \::::::::/    /         \:::\  /:::/    /        \:::\   \::/    /       /:::/   /
          /:::/    /           \::::::/    /           \:::\/:::/    /          \:::\   \/____/       /:::/   /
         /:::/    /             \::::/    /             \::::::/    /            \:::\    \          /:::/   /
        /:::/    /               \::/____/               \::::/    /              \:::\____\        /:::/   /
        \::/    /                 --                      \::/____/                \::/    /        \::/   /
         \/____/                                           --                       \/____/          \/___/
*/

#ifndef M7ENGINE_H
#define M7ENGINE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>

#ifdef _WIN32
#include <allegro5/allegro_direct3d.h>
#endif

#include "Entity.h"
#include "Sprite.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Vector2.h"
#include "Entity.h"
#include "ParticleEmitter.h"
#include "Primitives.h"
#include "Font.h"
#include "CollisionManager.h"
#include "ConfigReader.h"
#include "ResourceManager.h"
#include "Logger.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 3

namespace M7engine
{
class Engine
{
private:
	bool redraw;
	int screenWidth, screenHeight, colorDepth, frameRate, frameCount, windowMode, displayContext;
	double oldTime;
	float fps;
	std::list<Entity*> entities;
	std::list<ParticleEmitter*> particleEmitters;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *icon;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_TIMER *timer;

public:
	Engine();
	virtual ~Engine();

	bool init(int width, int height, int mode);
	void close();
	bool update();

	void updateEntities();
	void drawEntities();
	void cleanEntities();
	void addEntity(Entity *entity);
	Entity *findEntity(int id);
	std::list<Entity*> getEntityList() { return entities; }
	long getEntityCount() { return (long)entities.size(); }
	void reloadResources();

	void updateCollisions();

	ALLEGRO_DISPLAY* getDisplay() { return display; }
	ALLEGRO_EVENT_QUEUE* getEventQueue() { return eventQueue; }

	int getFrameRate() { return this->frameRate; }
	void setFrameRate(float arg) { this->frameRate = arg; al_set_timer_speed(timer, 1.0 / arg); }
	int getFrameCount() { return this->frameCount; }
	float getFPS() { return this->fps; }

	int getScreenWidth() { return this->screenWidth; }
	void setScreenWidth(int value) { this->screenWidth = value; }
	int getScreenHeight() { return this->screenHeight; }
	void setScreenHeight(int value) { this->screenHeight = value; }
	int getColorDepth() { return this->colorDepth; }
	void setColorDepth(int value) { this->colorDepth = value; }
	int getWindowMode() { return this->windowMode; }
	bool setWindowMode(int value);
	int getDisplayContext() { return this->displayContext; }
	bool setDisplayContext(int value);

	void setWindowTitle(const char *title) { al_set_window_title(display, title); }
	bool setIcon(const char *filename)
	{
		icon = al_load_bitmap(filename); if (!icon) { return false; } al_set_display_icon(display, icon); return true;
	}

	SoundManager *soundManager;
	FontManager *fontManager;
	Primitives *primitives;
	CollisionManager *collisionManager;
	ConfigReader *configReader;

	SoundManager* getSoundManager() { return soundManager; }
	FontManager* getFontManager() { return fontManager; }
	Primitives* getPrimitives() { return primitives; }
	CollisionManager* getCollisionManager() { return collisionManager; }
	ConfigReader* getConfigReader() { return configReader; }
};
};

#endif

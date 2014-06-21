/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  M7engine
 *  M7engine.h
 *  Purpose: Main engine class.
 *  @author David Houchin
 *  @version 1.0 7/17/14
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

namespace M7engine {
class Engine {
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

    /**
     *  Initialize engine with specified video mode. Returns true if successful.
     *  @param width Width of display resolution.
     *  @param height Height of display resolution.
     *  @param mode Window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    bool init(int width, int height, int mode);
    /**
     *  Unused
     */
    void close();
    /**
     *  Main update function to be called every frame.
     */
    bool update();
    /**
     *  Call update function of all registered entities.
     */
    void updateEntities();
    /**
     *  Call draw routines of all registered entities.
     */
    void drawEntities();
    /**
     *  Cleans inactive entities.
     */
    void cleanEntities();
    /**
     *  Register an entity and assigns an entity ID.
     *  @param *entity Pointer to entity to register.
     */
    void addEntity(Entity *entity);
    /**
     *  Returns a pointer to a requested entity ID.
     *  @param id ID of entity to find.
     *  @return Pointer of entity, if found.
     */
    Entity *findEntity(int id);
    /**
     *  Returns a pointer to the list of registered entities.
     *  @return A pointer to the list of registered entities.
     */
    std::list<Entity*> getEntityList() { return entities; }
    /**
     *  Return the number of registered entities.
     *  @return The number of registered entities.
     */
    long getEntityCount() { return (long)entities.size(); }
    /**
     *  Reloads volatile resources into memory.
     */
    void reloadResources();

    /**
     *  Updates the collision states of all registered entities.
     */
    void updateCollisions();

    /**
     *  Returns a pointer to the current ALLEGRO_DISPLAY rendered to.
     *  @return Pointer to currently used ALLEGRO_DISPLAY.
     */
    ALLEGRO_DISPLAY* getDisplay() { return display; }
    /**
     *  Returns a pointer the main engine event queue.
     *  @return Pointer to the mainly used ALLEGRO_EVENT_QUEUE.
     */
    ALLEGRO_EVENT_QUEUE* getEventQueue() { return eventQueue; }

    /**
     *  Returns the currently set frame rate.
     *  @return An Int containing currently set frame rate.
     */
    int getFrameRate() { return this->frameRate; }
    /**
     *  Set the frame rate engine runs on.
     *  @param rate Float to set framerate to.
     */
    void setFrameRate(float rate) { this->frameRate = rate; al_set_timer_speed(timer, 1.0 / rate); }
    /**
     *  Returns the number of frames since engine start.
     *  @return Int value of processed frames thus far.
     */
    int getFrameCount() { return this->frameCount; }
    /**
     *  Returns the currently achieved frames per second.
     *  @return Float of current FPS.
     */
    float getFPS() { return this->fps; }

    /**
     *  Returns the current screen width.
     *  @return Int of current screen width.
     */
    int getScreenWidth() { return this->screenWidth; }
    /**
     *  Set the screen width.
     *  @param width Int to set screen width to.
     */
    void setScreenWidth(int width) { this->screenWidth = width; }
    /**
     *  Returns the current screen height.
     *  @param level Int of current screen height.
     */
    int getScreenHeight() { return this->screenHeight; }
    /**
     *  Set the screen height.
     *  @param height Int to set screen height to.
     */
    void setScreenHeight(int height) { this->screenHeight = height; }
    /**
     *  Returns the currently used color depth.
     *  @return Int of current color depth..
     */
    int getColorDepth() { return this->colorDepth; }
    /**
     *  Set the color depth to use.
     *  @param level Int to set color depth.
     */
    void setColorDepth(int value) { this->colorDepth = value; }
    /**
     *  Returns the current window mode.
     *  @returns Int specifying window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    int getWindowMode() { return this->windowMode; }
    /**
     *  Set the window mode to use. Returns true if successful.
     *  @param mode Window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    bool setWindowMode(int mode);
    /**
     *  Returns the current display context.
     *  @return Int specifying display context. 0-DirectX. 1-OpenGL.
     */
    int getDisplayContext() { return this->displayContext; }
    /**
     *  Set the display context to use. Returns true if successful.
     *  @param context Int specifying display context. 0-DirectX. 1-OpenGL.
     */
    bool setDisplayContext(int context);
    /**
     *  Set the window title.
     *  @param title Char array containing window title to use.
     */

    void setWindowTitle(const char *title) { al_set_window_title(display, title); }
    /**
     *  Set the window icon to use. Returns true if successful.
     *  @param *filename Filename of icon bitmap to use.
     */
    bool setIcon(const char *filename) {
        icon = al_load_bitmap(filename); if (!icon) { return false; } al_set_display_icon(display, icon); return true;
    }

    /**
     *  Returns a char array containing the Allegro version number.
     *  @return Char array containing the Allegro version number.
     */
    const char* getAllegroVersion();

    SoundManager *soundManager;
    FontManager *fontManager;
    Primitives *primitives;
    CollisionManager *collisionManager;
    ConfigReader *configReader;

    /**
     *  Returns pointer to sound manager.
     *  @return Pointer to sound manager.
     */
    SoundManager* getSoundManager() { return soundManager; }
    /**
     *  Returns pointer to font manager.
     *  @return Pointer to font manager.
     */
    FontManager* getFontManager() { return fontManager; }
    /**
     *  Returns pointer to primitives manager.
     *  @return Pointer to primitives manager.
     */
    Primitives* getPrimitives() { return primitives; }
    /**
     *  Returns pointer to collision manager.
     *  @return Pointer to collision manager.
     */
    CollisionManager* getCollisionManager() { return collisionManager; }
    /**
     *  Returns pointer to configuration reader.
     *  @return Pointer to configuration reader.
     */
    ConfigReader* getConfigReader() { return configReader; }
};
};

#endif

/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
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
#include <vector>
#include <math.h>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>

#include "ConfigReader.h"
#include "Sprite.h"
#include "Entity.h"
#include "Collision.h"
#include "Input.h"
#include "Vector2.h"
#include "Logger.h"
#include "Timer.h"
#include "Text.h"
#include "Utilities.h"
#include "Sound.h"
#include "ResourceManager.h"
#include "Primitives.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1 //No definite versions at the alpha build point.

namespace M7engine {

class Engine {
private:
    Engine();
    static Engine* engineInstance;

    bool redraw;
    int screenWidth, screenHeight, colorDepth, frameRate, frameCount, windowMode, displayContext, frameDelay, currentFrameDelta, oldTime;
    int fps;

    const char* windowTitle;
    SDL_Surface* windowIcon;

    std::vector<Entity*> entities;
    std::vector<Tile*> tiles;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* winTexture;

    struct Viewport {
        int x;
        int y;
        int h;
        int w;
    } viewport;

    SDL_Surface* textSurface;
    SDL_Texture* textTexture;

    Timer timer;

    CollisionManager *collisionManager;
    ConfigReader *configReader;

public:
    /**
     * Returns the static instance of the engine.
     * @return Pointer to engine.
     */
    static Engine* getInstance();

    virtual ~Engine();

    /**
     *  Initialize engine with specified video mode. Returns true if successful.
     *  @param width Width of display resolution.
     *  @param height Height of display resolution.
     *  @param mode Window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    bool init(int width, int height, int mode);

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
    std::vector<Entity*> getEntityList() { return entities; }

    /**
     *  Return the number of registered entities.
     *  @return The number of registered entities.
     */
    long getEntityCount() { return (long)entities.size(); }

    struct entityDepthCompare
    {
        inline bool operator() (Entity *a, Entity *b)
        {
            return (a->getDepth() > b->getDepth());
        }
    };

    void sortEntitiesByDepth();

    /**
     *  Register a tile.
     *  @param *tile Pointer to tile to register.
     */
    void addTile(Tile *tile);

    /**
     *  Returns a pointer to the list of registered tiles.
     *  @return A pointer to the list of registered tiles.
     */
    std::vector<Tile*> getTileList() { return tiles; }

    /**
     *  Return the number of registered tiles.
     *  @return The number of registered tiles.
     */
    long getTileCount() { return (long)tiles.size(); }

    struct tileDepthCompare
    {
        inline bool operator() (Tile *a, Tile *b)
        {
            return (a->getDepth() > b->getDepth());
        }
    };

    void sortTilesByDepth();

    /**
     *  Call draw routines of all registered tiles.
     */
    void drawTiles();

    /**
     *  Updates the collision states of all registered entities.
     */
    void updateCollisions();

    /**
     *  Render a texture onto the display with default width and height.
     *  @param *texture SDL_Texture to render.
     *  @param x The X position to render texture at.
     *  @param y The Y position to render texture at.
     */
    void renderTexture(SDL_Texture *texture, int x, int y);

    /**
     *  Render a texture onto the display with default width and height.
     *  @param *texture SDL_Texture to render.
     *  @param x The X position to render texture at.
     *  @param y The Y position to render texture at.
     *  @param w The width to scale texture to.
     *  @param h The height to scale texture to.
     */
    void renderTexture(SDL_Texture *texture, int x, int y, int w, int h);

    void setViewport(int x, int y, int w, int h);

    int getViewportX() { return viewport.x; }

    int getViewportY() { return viewport.y; }

    int getViewportW() { return viewport.w; }

    int getViewportH() { return viewport.h; }

    /**
     *  Returns a pointer to the current window rendered to.
     *  @return Pointer to currently used SDL_Window.
     */
    SDL_Window* getWindow() { return window; }

    /**
     *  Returns a pointer to the current renderer.
     *  @return Pointer to currently used SDL_Renderer.
     */
    SDL_Renderer* getRenderer() { return renderer; }

    /**
     *  Returns the currently set frame rate.
     *  @return An Int containing currently set frame rate.
     */
    int getFrameRate() { return this->frameRate; }

    /**
     *  Returns the number of frames since engine start.
     *  @return Int value of processed frames thus far.
     */
    int getFrameCount() { return this->frameCount; }

    /**
     *  Returns the currently achieved frames per second.
     *  @return Float of current FPS.
     */
    int getFPS() { return this->fps; }

    /**
     *  Delays the engine to keep the engine at a set frame rate.
     */
    void delayFramerate();

    /**
     *  TODO
     */
    int getDelta() { return this->currentFrameDelta; }

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
    void setWindowTitle(const char *title) { windowTitle = title; SDL_SetWindowTitle(window, title); }

    /**
     *  Set the window icon to use. Returns true if successful.
     *  @param *filename Filename of icon bitmap to use.
     */
    bool setWindowIcon(const char *filename) {
        windowIcon = IMG_Load(filename); if (!windowIcon) { return false; } SDL_SetWindowIcon(window, windowIcon); return true;
    }

    /**
     *  Render text onto the display.
     *  @param x The X position to render text at.
     *  @param y The Y position to render text at.
     *  @param *font The font to use.
     *  @param *text The actual text to render.
     */
    void renderText(float x, float y, Font *font, char const *text);

    /**
     *  Render text onto the display.
     *  @param x The X position to render text at.
     *  @param y The Y position to render text at.
     *  @param *font The font to use.
     *  @param *text The actual text to render.
     */
    void renderTextF(float x, float y, Font *font, char const *text, ...);

    /**
     *  Play the given sound.
     *  @param *sound The sound to play.
     *  @param repeat The number of repeats to play sound, i.e. 0 means play once.
     *  @return Int of the channel sound was assigned to.
     */
    int playSound(Sound* sound, int repeat);

    /**
     *  Pause sound on given channel.
     *  @param channel The channel to pause sound on.
     */
    void pauseSound(int channel);

    /**
     *  Stop sound on given channel.
     *  @param channel The channel to stop sound on. Use -1 for all channels.
     */
    void stopSound(int channel);

    /**
     *  Checks if given channel is playing a sound.
     *  @param channel The channel to check.
     *  @return Int of whether channel is playing sound.
     */
    int isPlaying(int channel);

    /**
     *  Play the given music.
     *  @param *music The music to play.
     */
    void playMusic(Mix_Music* music);

    /**
     *  Pause the currently playing music.
     */
    void pauseMusic();

    /**
     *  Stop the current music.
     */
    void stopMusic();

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

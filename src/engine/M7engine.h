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
#include <string>
#include <sstream>

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
#include "Console.h"
#include "Widget.h"
#include "Window.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

namespace M7engine {

class Engine {
public:
    /**
     * @brief Returns the static instance of the engine.
     * @return Pointer to engine.
     */
    static Engine* getInstance();

    virtual ~Engine();

    /**
     *  @brief Initialize engine with specified video mode. Returns true if successful.
     *  @param width Width of display resolution.
     *  @param height Height of display resolution.
     *  @param mode Window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    bool init(int width, int height, int mode);

    /**
     *  @brief Main update function to be called every frame.
     */
    bool update();

    /**
     *  @brief Call update function of all registered entities.
     */
    void updateEntities();

    /**
     *  @brief Call draw routines of all registered entities.
     */
    void drawEntities();

    /**
     *  @brief Cleans inactive entities.
     */
    void cleanEntities();

    /**
     *  @brief Register an entity and assigns an entity ID.
     *  @param *entity Pointer to entity to register.
     */
    void addEntity(Entity *entity);

    /**
     *  @brief Deletes the entity with the passed entity ID.
     *  @param id ID of entity to remove.
     */
    void destroyEntity(int id);

    /**
     *  @brief Deletes all registered entities.
     */
    void destroyAllEntities();

    /**
     *  @brief Returns a pointer to a requested entity ID.
     *  @param id ID of entity to find.
     *  @return Pointer of entity, if found.
     */
    Entity *findEntity(int id);

    /**
     *  @brief Returns a pointer to the list of registered entities.
     *  @return A pointer to the list of registered entities.
     */
    std::vector<Entity*>& getEntityList() { return entities; }

    /**
     *  @brief Return the number of registered entities.
     *  @return The number of registered entities.
     */
    long getEntityCount() { return (long)entities.size(); }

    /**
     *  @brief Sort all registered entities by their drawing depths.
     */
    void sortEntitiesByDepth();

    /**
     *  @brief Register a tile.
     *  @param *tile Pointer to tile to register.
     */
    void addTile(Tile *tile);

    /**
     *  @brief Deletes the tile that is passed.
     *  @param *tile Pointer to tile to remove.
     */
    void destroyTile(Tile *deleteTile);

    /**
     *  @brief Deletes all registered tiles.
     */
    void destroyAllTiles();

    /**
     *  @brief Returns a pointer to the list of registered tiles.
     *  @return A pointer to the list of registered tiles.
     */
    std::vector<Tile*>& getTileList() { return tiles; }

    /**
     *  @brief Return the number of registered tiles.
     *  @return The number of registered tiles.
     */
    long getTileCount() { return (long)tiles.size(); }

    /**
     *  @brief Sort all registered tiles by their drawing depths.
     */
    void sortTilesByDepth();

    /**
     *  @brief Call draw routines of all registered tiles.
     */
    void drawTiles();

    /**
     *  @brief Updates the collision states of all registered entities.
     */
    void updateCollisions();

    /**
     *  @brief Render a texture onto the display with default width and height.
     *  @param *texture SDL_Texture to render.
     *  @param x The X position to render texture at.
     *  @param y The Y position to render texture at.
     */
    void renderTexture(SDL_Texture *texture, int x, int y);

    /**
     *  @brief Render a texture onto the display with default width and height.
     *  @param *texture SDL_Texture to render.
     *  @param x The X position to render texture at.
     *  @param y The Y position to render texture at.
     *  @param w The width to scale texture to.
     *  @param h The height to scale texture to.
     */
    void renderTexture(SDL_Texture *texture, int x, int y, int w, int h);

    /**
     *  @brief Set the position of the viewport.
     *  @param x The X position of the viewport's top left corner.
     *  @param y The Y position of the viewport's top left corner.
     *  @param w The width of the viewport.
     *  @param h The height of the viewport.
     */
    void setViewport(int x, int y, int w, int h);

    /**
     *  @brief Returns the X position of the viewport's top left corner.
     *  @return X position of viewport.
     */
    int getViewportX() { return viewport.x; }

    /**
     *  @brief Returns the Y position of the viewport's top left corner.
     *  @return Y position of viewport.
     */
    int getViewportY() { return viewport.y; }

    /**
     *  @brief Returns the width of the viewport.
     *  @return Width of viewport.
     */
    int getViewportW() { return viewport.w; }

    /**
     *  @brief Returns the height of the viewport.
     *  @return Height of viewport.
     */
    int getViewportH() { return viewport.h; }

    /**
     *  @brief Returns a pointer to the current window rendered to.
     *  @return Pointer to currently used SDL_Window.
     */
    SDL_Window* getWindow() { return window; }

    /**
     *  @brief Returns a pointer to the current renderer.
     *  @return Pointer to currently used SDL_Renderer.
     */
    SDL_Renderer* getRenderer() { return renderer; }

    /**
     *  @brief Returns the currently set frame rate.
     *  @return An Int containing currently set frame rate.
     */
    int getFrameRate() { return this->frameRate; }

    /**
     *  @brief Returns the number of frames since engine start.
     *  @return Int value of processed frames thus far.
     */
    int getFrameCount() { return this->frameCount; }

    /**
     *  @brief Returns the currently achieved frames per second.
     *  @return Float of current FPS.
     */
    int getFPS() { return this->fps; }

    /**
     *  @brief Sets the frame delay to used per engine cycle.
     *  @param delay The target delay.
     */
    void setFrameDelay(int delay) { this->frameDelay = delay; }

    /**
     *  @brief Delays the engine to keep the engine at a set frame rate.
     */
    void delayFramerate();

    /**
     *  TODO
     */
    int getDelta() { return this->currentFrameDelta; }

    /**
     *  @brief Returns the current screen width.
     *  @return Int of current screen width.
     */
    int getScreenWidth() { return this->screenWidth; }

    /**
     *  @brief Set the screen width.
     *  @param width Int to set screen width to.
     */
    void setScreenWidth(int width) { this->screenWidth = width; }

    /**
     *  @brief Returns the current screen height.
     *  @param level Int of current screen height.
     */
    int getScreenHeight() { return this->screenHeight; }

    /**
     *  @brief Set the screen height.
     *  @param height Int to set screen height to.
     */
    void setScreenHeight(int height) { this->screenHeight = height; }

    /**
     *  @brief Returns the currently used color depth.
     *  @return Int of current color depth..
     */
    int getColorDepth() { return this->colorDepth; }

    /**
     *  @brief Set the color depth to use.
     *  @param level Int to set color depth.
     */
    void setColorDepth(int value) { this->colorDepth = value; }

    /**
     *  @brief Returns the current window mode.
     *  @returns Int specifying window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    int getWindowMode() { return this->windowMode; }

    /**
     *  @brief Set the window mode to use. Returns true if successful.
     *  @param mode Window mode. 0-Windowed. 1-Fullscreen. 2-Fullscreen Windowed.
     */
    bool setWindowMode(int mode);

    /**
     *  @brief Returns the current display context.
     *  @return Int specifying display context. 0-DirectX. 1-OpenGL.
     */
    int getDisplayContext() { return this->displayContext; }

    /**
     *  @brief Set the display context to use. Returns true if successful.
     *  @param context Int specifying display context. 0-DirectX. 1-OpenGL.
     */
    bool setDisplayContext(int context);

    /**
     *  @brief Set the window title.
     *  @param title Char array containing window title to use.
     */
    void setWindowTitle(const char *title) { windowTitle = title; SDL_SetWindowTitle(window, title); }

    /**
     *  @brief Set the window icon to use. Returns true if successful.
     *  @param *filename Filename of icon bitmap to use.
     */
    bool setWindowIcon(const char *filename) {
        windowIcon = IMG_Load(filename); if (!windowIcon) { return false; } SDL_SetWindowIcon(window, windowIcon); return true;
    }

    /**
     *  @brief Render text onto the display.
     *  @param x The X position to render text at.
     *  @param y The Y position to render text at.
     *  @param *font The font to use.
     *  @param *text The actual text to render.
     */
    void renderText(float x, float y, Font *font, char const *text);

    /**
     *  @brief Render text onto the display.
     *  @param x The X position to render text at.
     *  @param y The Y position to render text at.
     *  @param *font The font to use.
     *  @param *text The actual text to render.
     */
    void renderTextF(float x, float y, Font *font, char const *text, ...);

    /**
     *  @brief Play the given sound.
     *  @param *sound The sound to play.
     *  @param repeat The number of repeats to play sound, i.e. 0 means play once.
     *  @return Int of the channel sound was assigned to.
     */
    int playSound(Sound* sound, int repeat);

    /**
     *  @brief Pause sound on given channel.
     *  @param channel The channel to pause sound on.
     */
    void pauseSound(int channel);

    /**
     *  @brief Stop sound on given channel.
     *  @param channel The channel to stop sound on. Use -1 for all channels.
     */
    void stopSound(int channel);

    /**
     *  @brief Checks if given channel is playing a sound.
     *  @param channel The channel to check.
     *  @return Int of whether channel is playing sound.
     */
    int isPlaying(int channel);

    /**
     *  @brief Play the given music.
     *  @param *music The music to play.
     */
    void playMusic(Mix_Music* music);

    /**
     *  @brief Pause the currently playing music.
     */
    void pauseMusic();

    /**
     *  @brief Stop the current music.
     */
    void stopMusic();

    /**
     *  @brief Set whether or not to draw entity bounding boxes.
     */
    void toggleDrawBoundingBoxes() { drawBoundingBoxes = !drawBoundingBoxes; }

    /**
     *  @brief Set whether to cap the framerate or not.
     */
    void toggleFrameCap() { fpsCap = !fpsCap; }

    /**
      *  @brief Returns pointer to collision manager.
      *  @return Pointer to collision manager.
      */
    CollisionManager* getCollisionManager() { return collisionManager; }

    /**
      *  @brief Returns pointer to configuration reader.
      *  @return Pointer to configuration reader.
      */
    ConfigReader* getConfigReader() { return configReader; }

    Console* getConsole() { return console; }

    std::string getVersion();

private:
    Engine();
    static Engine* engineInstance;

    bool redraw, drawBoundingBoxes, fpsCap;
    int screenWidth, screenHeight, colorDepth, frameRate, frameCount, windowMode, displayContext, frameDelay, currentFrameDelta, oldTime, fps;

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

    CollisionManager* collisionManager;
    ConfigReader* configReader;
    Console* console;

    //This struct is used for comparing entity depth values when sorting.
    struct entityDepthCompare
    {
        inline bool operator() (Entity* a, Entity* b)
        {
            return (a->getDepth() > b->getDepth());
        }
    };

    //This struct is used for comparing tile depth values when sorting.
    struct tileDepthCompare
    {
        inline bool operator() (Tile* a, Tile* b)
        {
            return (a->getDepth() > b->getDepth());
        }
    };
};
};

#endif

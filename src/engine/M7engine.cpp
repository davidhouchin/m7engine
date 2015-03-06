/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  M7engine
 *  M7engine.cpp
 *  Purpose: Main engine class.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "M7engine.h"

namespace M7engine {
Engine* Engine::engineInstance = NULL;

Engine* Engine::getInstance()
{
    if (!engineInstance) {
        engineInstance = new Engine;
    }

    return engineInstance;
}

Engine::Engine()
{
    frameDelay = 30;
    frameCount = 0;
    fps = 0;
    fpsCap = true;

    this->setScreenWidth(640);
    this->setScreenHeight(480);
    this->setColorDepth(32);
    this->windowMode = 0;

    drawBoundingBoxes = false;

    configReader = new ConfigReader;
    console = Console::getInstance();
}

Engine::~Engine()
{
    Logger::getInstance()->logMessage(0, "Cleaning up resources...");

    destroyAllEntities();
    destroyAllTiles();

    SDL_FreeSurface(windowIcon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();

    delete InputManager::getInstance();
    delete Logger::getInstance();
    delete configReader;
    delete collisionManager;
    delete console;
}

bool Engine::init(int width, int height, int mode)
{
    this->setScreenWidth(width);
    this->setScreenHeight(height);

    viewport.x = 0;
    viewport.y = 0;
    viewport.w = width;
    viewport.h = height;

    if (SDL_Init(0) < 0) {
        Logger::getInstance()->logError(0, "SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    int flags = (SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if (SDL_InitSubSystem(flags) < 0) {
        Logger::getInstance()->logError(0, "SDL_InitSubSystem failed: %s", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Logger::getInstance()->logError(0, "IMG_Init failed: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        Logger::getInstance()->logError(0, "TTF_Init failed: %s", TTF_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Logger::getInstance()->logError(0, "MIX_OpenAudio failed: %s", Mix_GetError());
        return false;
    }

    switch (mode) {
        case 0: this->windowMode = 0; window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN); break; //Set windowed
        case 1: this->windowMode = 1; window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN); break; //Set fullscreen
        case 2: this->windowMode = 2; window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP); break; //Set fullscreen-windowed
    }

    if (window == NULL) {
        Logger::getInstance()->logError(0, "Failed to create main display: %s", SDL_GetError());
        return false;
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        if (renderer == NULL) {
            Logger::getInstance()->logError(0, "Failed to create SDL renderer: %s", SDL_GetError());
        } else {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }

    winTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);

    collisionManager = new CollisionManager;

    timer.start();
    oldTime = SDL_GetTicks();

    return true;
}

bool Engine::update()
{
    Logger::getInstance()->logMessage(99, "Engine update cycle: %i", frameCount);

    int frameTime = SDL_GetTicks();
    fps = (frameTime - oldTime);
    oldTime = frameTime;

    frameCount++;

    InputManager::getInstance()->update();

    if (InputManager::getInstance()->hasQuit()) {
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    SDL_SetRenderTarget(renderer, winTexture);
    SDL_RenderClear(renderer);

    drawTiles();
    drawEntities();
    updateCollisions();
    updateEntities();

    WindowManager::getInstance()->update();

    console->update();
    console->draw();

    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, winTexture, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    cleanEntities();

    delayFramerate();

    Logger::getInstance()->logMessage(99, "Engine update cycle complete");

    return true;
}

void Engine::delayFramerate()
{
    if (!fpsCap) {
        return;
    }

    currentFrameDelta = timer.getDelta();

    if ((currentFrameDelta) < (frameDelay)) {
        SDL_Delay(frameDelay - currentFrameDelta);
    }

    timer.restart();
}

void Engine::setViewport(int x, int y, int w, int h)
{
    viewport.x = x;
    viewport.y = y;
    viewport.w = w;
    viewport.h = h;
}

void Engine::renderTexture(SDL_Texture* texture, int x, int y)
{
    if (texture == NULL) {
        Logger::getInstance()->logError(0, "renderTexture failed: Texture doesn't exist");
    } else {
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        renderTexture(texture, x, y, w, h);
    }
}

void Engine::renderTexture(SDL_Texture* texture, int x, int y, int w, int h)
{
    if (texture == NULL) {
        Logger::getInstance()->logError(0, "renderTexture failed: Texture doesn't exist");
    } else {
        SDL_Rect dest;
        dest.x = x - viewport.x;
        dest.y = y - viewport.y;
        dest.w = w;
        dest.h = h;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
}

void Engine::renderText(float x, float y, Font* font, const char* text)
{
    if (font == NULL) {
        Logger::getInstance()->logError(0, "drawText failed: Font doesn't exist");
    } else {
        textSurface = TTF_RenderText_Blended(font->getFont(), text, font->getSDLColor());
        textTexture = SDL_CreateTextureFromSurface(getRenderer(), textSurface);

        renderTexture(textTexture, x, y);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void Engine::renderTextF(float x, float y, Font* font, const char* text, ...)
{
    if (font == NULL) {
        Logger::getInstance()->logError(0, "drawTextF failed: Font doesn't exist");
    } else {
        char buffer[99];
        va_list args;
        va_start(args, text);
        vsprintf(buffer, text, args);

        textSurface = TTF_RenderText_Blended(font->getFont(), buffer, font->getSDLColor());
        textTexture = SDL_CreateTextureFromSurface(getRenderer(), textSurface);

        renderTexture(textTexture, x, y);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        va_end(args);
    }
}

void Engine::updateEntities()
{
    Logger::getInstance()->logMessage(99, "Engine is updating entities");

    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (!entity->killMe) {
            if (entity->getActive()) {
                entity->updateTimers();
                entity->update();
                entity->move();
            }
            iter++;
        } else {
            iter = entities.erase(iter);
            delete entity;
        }
    }
}

void Engine::drawEntities()
{
    Logger::getInstance()->logMessage(99, "Engine is drawing");

    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getVisible()) {
            entity->draw();
            if (drawBoundingBoxes) {
                drawRectangle(entity->getXBBox(), entity->getYBBox(), entity->getWBBox(), entity->getHBBox(), 255, 255, 0, 150);
            }
        }
        iter++;
    }
}

void Engine::cleanEntities()
{
    Logger::getInstance()->logMessage(99, "Engine is cleaning");

    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (!entity->getActive()) {
            entities.erase(iter);
        } else {
            iter++;
        }
    }
}

void Engine::addEntity(Entity *entity)
{
    static int id = 0;
    entity->setID(id);
    entities.push_back(entity);
    Logger::getInstance()->logMessage(1, "Engine added entity id: %i", id);
    id++;
}

Entity* Engine::findEntity(int id)
{
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getID() == id) {
            return entity;
        } else {
            iter++;
        }
    }
    return NULL;
}

void Engine::destroyEntity(int id)
{
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getID() == id) {
            //entities.erase(iter);
            //delete entity;
            entity->killMe = true;
            return;
        } else {
            iter++;
        }
    }
}

void Engine::destroyAllEntities()
{
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i] != NULL) {
            delete entities[i];
        }
    }

    entities.clear();
}

void Engine::sortEntitiesByDepth()
{
    std::sort(entities.begin(), entities.end(), entityDepthCompare());
}

void Engine::updateCollisions()
{
    Logger::getInstance()->logMessage(99, "Engine is updating collisions");

    std::vector<Entity*>::iterator iterA, iterB;
    Entity *entityA;
    Entity *entityB;
    iterA = entities.begin();
    iterB = entities.begin();

    while (iterA != entities.end()) {
        entityA = *iterA;

        while (iterB != entities.end()) {
            entityB = *iterB;
            if ((entityA != entityB) && (collisionManager->getIntersect(entityA->getBBox(), entityB->getBBox()))) {
                entityA->collision(entityB);
            }
            iterB++;
        }
        iterB = entities.begin();
        iterA++;
    }
}

void Engine::addTile(Tile *tile)
{
    tiles.push_back(tile);
}

void Engine::destroyTile(Tile *deleteTile)
{
    std::vector<Tile*>::iterator iter;
    Tile *tile;
    iter = tiles.begin();

    while (iter != tiles.end()) {
        tile = *iter;
        if (tile == deleteTile) {
            tiles.erase(iter);
            delete tile;
        } else {
            iter++;
        }
    }
}

void Engine::sortTilesByDepth()
{
    std::sort(tiles.begin(), tiles.end(), tileDepthCompare());
}

void Engine::drawTiles()
{
    Logger::getInstance()->logMessage(99, "Engine is drawing tiles");

    std::vector<Tile*>::iterator iter;
    Tile *tile;
    iter = tiles.begin();

    while (iter != tiles.end()) {
        tile = *iter;
        tile->draw();
        iter++;
    }
}

void Engine::destroyAllTiles()
{
    for (size_t i = 0; i < tiles.size(); i++) {
        if (tiles[i] != NULL) {
            delete tiles[i];
        }
    }

    tiles.clear();
}

bool Engine::setWindowMode(int value)
{
    switch (value) {
    case 0:
        Logger::getInstance()->logMessage(0, "Changing to windowed mode...");
        if (SDL_SetWindowFullscreen(window, 0)) { Logger::getInstance()->logError(0, "Failed to change to windowed mode"); return 1; }
        this->windowMode = 0;
        break;
    case 1:
        Logger::getInstance()->logMessage(0, "Changing to fullscreen mode...");
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN)) { Logger::getInstance()->logError(0, "Failed to change to fullscreen mode"); return 1; }
        this->windowMode = 1;
        break;
    case 2:
        Logger::getInstance()->logMessage(0, "Changing to fullscreen windowed mode...");
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP)) { Logger::getInstance()->logError(0, "Failed to change to fullscreen windowed mode"); return 1; }
        this->windowMode = 2;
        break;
    }

    return 0;
}

int Engine::playSound(Sound* sound, int repeat)
{
    int channel = Mix_PlayChannel(-1, sound->getSound(), repeat);

    if (channel == -1) {
        Logger::getInstance()->logError(0, "playSound failed: %s", Mix_GetError());
    }

    return channel;
}

void Engine::pauseSound(int channel)
{
    Mix_Pause(channel);
}

void Engine::stopSound(int channel)
{
    Mix_HaltChannel(channel);
}

int Engine::isPlaying(int channel)
{
    return Mix_Playing(channel);
}

void Engine::playMusic(Mix_Music* music)
{
    Mix_PlayMusic(music, -1);
}

void Engine::pauseMusic()
{
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

void Engine::stopMusic()
{
    Mix_HaltMusic();
}

std::string Engine::getVersion()
{
    std::stringstream version;

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    version << "Engine: " << VERSION_MAJOR << "." << VERSION_MINOR <<
               " " << __DATE__ << " " << __TIME__ << "  " <<
               "SDL-Compiled: " << std::to_string(compiled.major) << "." << std::to_string(compiled.minor) << "." << std::to_string(compiled.patch) <<
               " SDL-Linked: " << std::to_string(linked.major) << "." << std::to_string(linked.minor) << "." << std::to_string(linked.patch);

    return version.str();
}

};

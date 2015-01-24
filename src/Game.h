/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Game
 *  Game.h
 *  Purpose: Main game class.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#ifndef GAME_H
#define GAME_H

#include "engine/M7engine.h"

using namespace M7engine;

namespace SampleGame {

class Level;
class LevelEditor;

class Game {
private:
    Engine *engine;
    Logger *logger;
    InputManager *input;
    ResourceManager *resources;
    CollisionManager *cManager;
    WindowManager *wm;
    ConfigReader *oConfig;
    Level *level;
    LevelEditor *levelEditor;

public:
    Game(std::string configFile);
    virtual ~Game();

    bool initObjects();

    bool run();

    bool loadLevel(std::string filename);

    Engine* getEngine(){return this->engine;}
    Logger* getLogger(){return this->logger;}
    InputManager* getInput(){return this->input;}
    ResourceManager* getResourceManager(){return this->resources;}
    CollisionManager* getCollisionManager(){return this->engine->getCollisionManager();}
    WindowManager* getWindowManager(){return this->wm;}
    ConfigReader* getObjectConfig(){return this->oConfig;}
};
}

#endif

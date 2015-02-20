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
class Monster;

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

    bool isEditorOpen;

    std::vector<Monster*> monsters;

public:
    Game(std::string configFile);
    virtual ~Game();

    bool initObjects();

    bool run();

    void turn();

    bool getEditorOpen() { return this->isEditorOpen; }

    void addMonster(Monster *monster);
    void killMonster(int id);
    std::vector<Monster*>& getMonsterList() { return this->monsters; }

    bool loadLevel(std::string filename);
    int getLevelWidth();
    void setLevelWidth(int width);
    int getLevelHeight();
    void setLevelHeight(int height);

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

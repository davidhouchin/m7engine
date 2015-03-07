/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Game
 *  Game.cpp
 *  Purpose: Main game class.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#include "Game.h"
#include "Level.h"
#include "LevelEditor.h"

namespace SampleGame {
Game::Game(std::string configFile)
{
    this->engine = Engine::getInstance();
    this->logger = Logger::getInstance();
    this->input = InputManager::getInstance();
    this->resources = ResourceManager::getInstance();
    this->cManager = engine->getCollisionManager();
    this->wm = WindowManager::getInstance();
    this->oConfig = new ConfigReader;

    isEditorOpen = false;

    //Start log
    logger->setLogFile("game.log");
    logger->logMessage(0, "Engine started");

    //Begin reading config values
    int resX, resY, fs;
    ConfigReader *config = engine->getConfigReader();

    config->loadConfig(configFile);

    logger->setLoggingLevel(config->getInt("debug", "log", 0));

    resX = config->getInt("video", "resX", 640);
    resY = config->getInt("video", "resY", 480);
    fs = config->getInt("video", "fs", 0);

    logger->logMessage(0, "Read config values: %i %i %i", resX, resY, fs);

    //Start engine
    engine->init(resX, resY, fs);
    engine->setWindowTitle(config->getString("base", "title", "").c_str());
    engine->setWindowIcon(config->getString("base", "icon", "").c_str());

    if (config->getBool("debug", "drawbboxes", false) == true) {
        engine->toggleDrawBoundingBoxes();
    }

    //Load resources
    resources->setPath(config->getString("base", "respath"));
    resources->loadConfig(config->getString("base", "resconf"));

    //Start monitoring input
    input->init();

    //Load widget config
    wm->loadConfig("../resources/widget.ini");

    //Give the console it's font
    engine->getConsole()->setFont(resources->getFont("veramono"));
}

Game::~Game()
{
    delete engine;
}

bool Game::initObjects()
{
    if (!oConfig->loadConfig("../resources/objects.ini")) {
        return false;
    }

    //Game objects
    level = new Level(this);
    if (!level->load("../resources/maps/test.map")) {
        return false;
    }

    levelEditor = new LevelEditor(this,
                                  engine->getViewportX()+64,
                                  engine->getViewportY()+64,
                                  275,
                                  300);
    levelEditor->setVisible(false);
    wm->addWindow(levelEditor);

    return true;
}

int Game::getLevelWidth()
{
    return level->getWidth();
}

void Game::setLevelWidth(int width)
{
    level->setWidth(width);
}

int Game::getLevelHeight()
{
    return level->getHeight();
}

void Game::setLevelHeight(int height)
{
    level->setHeight(height);
}

bool Game::loadLevel(std::string filename)
{
    if (!level->load(filename)) {
        return false;
    }

    return true;
}

bool Game::run()
{
    if (!engine->update()) {
        return false;
    }

    if (input->getKeyReleased(KEY_ESCAPE)) {
        return false;
    }

    if (input->getKeyReleased(KEY_F4)) {
        switch (engine->getWindowMode()) {
        case 0: engine->setWindowMode(1); break;
        case 1: engine->setWindowMode(2); break;
        case 2: engine->setWindowMode(0); break;
        }
    }

    if ((input->getKeyHeld(KEY_LEFT_SHIFT)) && (input->getKeyReleased(KEY_E))) {
        if (!levelEditor->getVisible()) {
            levelEditor->setVisible(true);
            isEditorOpen = true;
        } else {
            levelEditor->setVisible(false);
            isEditorOpen = false;
            engine->sortEntitiesByDepth();
            engine->sortTilesByDepth();
        }
    }

    return true;
}

void Game::addMonster(Monster *monster)
{
    static int mId = 0;
    monster->setMonsterID(mId);
    monsters.push_back(monster);
    mId++;
}

void Game::killMonster(int id)
{
    std::vector<Monster*>::iterator iterM;
    Monster *monster;
    iterM = monsters.begin();

    while (iterM != monsters.end()) {
        monster = *iterM;
        if (monster->getMonsterID() == id) {
            monsters.erase(iterM);
            return;
        }
        iterM++;
    }
}

void Game::turn()
{
    std::vector<Monster*>::iterator iterM;
    Monster *monster;
    iterM = monsters.begin();

    while (iterM != monsters.end()) {
        monster = *iterM;
        if (!monster->killMe) {
            monster->turn();
        }
        iterM++;
    }
}

}

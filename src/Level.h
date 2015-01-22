/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Level
 *  Level.h
 *  Purpose: Main level class.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */


#ifndef LEVEL_H
#define LEVEL_H

#include "Game.h"
#include "Player.h"
#include "Enemies.h"
#include "Props.h"

namespace SampleGame {
class Level {
private:
    std::string filename;
    int interval;
    int width;
    int height;

    Game *game;
public:
    Level(Game *game);
    bool load(std::string filename);
};
}

#endif

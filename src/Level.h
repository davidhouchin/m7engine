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

    enum mapObject {
        eWidth, eHeight,
        ePlayer,
        eMonster_ghost, eMonster_wraith, eMonster_specter, eMonster_zombie,
        eMonster_skeleton, eMonster_skeletonCaptain, eMonster_skeletonMage,
        eMonster_vampire,
        eFloor_brick, eFloor_brickVines, eFloor_brickMold, eFloor_dirt,
        eFloor_grass, eFloor_water, eFloor_water2, eFloor_lava, eFloor_lava2,
        eWall_brick, eWall_brickVines, eWall_brickMold, eWall_brickStairsDown,
        eWall_brickStairsUp, eWall_brickDoorClosed, eWall_brickDoorOpen,
        eWall_brickGateClosed, eWall_brickGateOpen, eWall_brickGrate,
        eNone
    };

    Level::mapObject translateString(std::string const& str);

public:
    Level(Game *game);

    bool load(std::string filename);

    int getWidth() { return this->width; }

    int getHeight() { return this->height; }
};
}

#endif

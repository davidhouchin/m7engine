/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Props
 *  Props.cpp
 *  Purpose: Misc. objects classes.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#include "Props.h"
#include "Game.h"

namespace SampleGame {
Floor_brick::Floor_brick(Game *game)
{
    setName("floor_brick");
    setProperties(game->getObjectConfig(), getName());
}

Floor_brickVines::Floor_brickVines(Game *game)
{
    setName("floor_brickVines");
    setProperties(game->getObjectConfig(), getName());
}

Floor_brickMold::Floor_brickMold(Game *game)
{
    setName("floor_brickMold");
    setProperties(game->getObjectConfig(), getName());
}

Floor_dirt::Floor_dirt(Game *game)
{
    setName("floor_dirt");
    setProperties(game->getObjectConfig(), getName());
}

Floor_grass::Floor_grass(Game *game)
{
    setName("floor_grass");
    setProperties(game->getObjectConfig(), getName());
}

Floor_water::Floor_water(Game *game)
{
    setName("floor_water");
    setProperties(game->getObjectConfig(), getName());
}

Floor_water2::Floor_water2(Game *game)
{
    setName("floor_water2");
    setProperties(game->getObjectConfig(), getName());
}

Floor_lava::Floor_lava(Game *game)
{
    setName("floor_lava");
    setProperties(game->getObjectConfig(), getName());
}

Floor_lava2::Floor_lava2(Game *game)
{
    setName("floor_lava2");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brick::Wall_brick(Game *game)
{
    setName("wall_brick");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickVines::Wall_brickVines(Game *game)
{
    setName("wall_brickVines");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickMold::Wall_brickMold(Game *game)
{
    setName("wall_brickMold");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickStairsDown::Wall_brickStairsDown(Game *game)
{
    setName("wall_brickStairsDown");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickStairsUp::Wall_brickStairsUp(Game *game)
{
    setName("wall_brickStairsUp");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickDoorClosed::Wall_brickDoorClosed(Game *game)
{
    setName("wall_brickDoorClosed");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickDoorOpen::Wall_brickDoorOpen(Game *game)
{
    setName("wall_brickDoorOpen");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickGateClosed::Wall_brickGateClosed(Game *game)
{
    setName("wall_brickGateClosed");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickGateOpen::Wall_brickGateOpen(Game *game)
{
    setName("wall_brickGateOpen");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickGrate::Wall_brickGrate(Game *game)
{
    setName("wall_brickGrate");
    setProperties(game->getObjectConfig(), getName());
}
}

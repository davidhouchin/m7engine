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

Wall_brick::Wall_brick(Game *game)
{
    setName("wall_brick");
    setProperties(game->getObjectConfig(), getName());
}
}

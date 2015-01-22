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
Coin::Coin(Game *game)
{
    setName("coin");
    setProperties(game->getObjectConfig(), getName());
}

Wall::Wall(Game *game)
{
    setName("wall");
    setProperties(game->getObjectConfig(), getName());
}

Tree::Tree(Game *game)
{
    setName("tree");
    setProperties(game->getObjectConfig(), getName());
}

Dirt::Dirt(Game *game)
{
    setName("dirt");
    setProperties(game->getObjectConfig(), getName());
}

Grass::Grass(Game *game)
{
    setName("grass");
    setProperties(game->getObjectConfig(), getName());
}
}

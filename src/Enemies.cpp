/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Enemies
 *  Enemies.cpp
 *  Purpose: Enemy character classes.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#include "Enemies.h"
#include "Game.h"

namespace SampleGame {
Monster_skeleton::Monster_skeleton(Game *game)
{
    this->game = game;
    setName("monster_skeleton");
    setProperties(game->getObjectConfig(), getName());
    hSpeed = 3;
}

void Monster_skeleton::update()
{
}

void Monster_skeleton::collision(Entity *other)
{
    if (other->getSolid()) {
        hSpeed = (hSpeed * -1);
    }
}
}

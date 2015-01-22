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
EnemyH::EnemyH(Game *game)
{
    this->game = game;
    setName("zombie");
    setProperties(game->getObjectConfig(), getName());
    setImage(game->getResourceManager()->getSprite("zombieright"));
    hSpeed = 4;
}

void EnemyH::update()
{
}

void EnemyH::collision(Entity *other)
{
    if (other->getSolid()) {
        hSpeed = (hSpeed * -1);
        if (this->getSprite()->getName() != "zombieleft") {
            setImage(game->getResourceManager()->getSprite("zombieleft"));
        } else {
            setImage(game->getResourceManager()->getSprite("zombieright"));
        }
    }
}

EnemyV::EnemyV(Game *game)
{
    this->game = game;
    setName("zombie");
    setProperties(game->getObjectConfig(), getName());
    vSpeed = 4;
}

void EnemyV::update()
{
}

void EnemyV::collision(Entity *other)
{
    if (other->getSolid()) {
        vSpeed = (vSpeed * -1);
        if (this->getSprite()->getName() != "zombieup") {
            setImage(game->getResourceManager()->getSprite("zombieup"));
        } else {
            setImage(game->getResourceManager()->getSprite("zombiedown"));
        }
    }
}
}

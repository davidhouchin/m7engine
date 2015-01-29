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
Monster_ghost::Monster_ghost(Game *game)
{
    this->game = game;
    setName("monster_ghost");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_ghost::update()
{
}

void Monster_ghost::collision(Entity *other)
{
}

void Monster_ghost::turn()
{
}

Monster_wraith::Monster_wraith(Game *game)
{
    this->game = game;
    setName("monster_wraith");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_wraith::update()
{
}

void Monster_wraith::collision(Entity *other)
{
}

void Monster_wraith::turn()
{
}

Monster_specter::Monster_specter(Game *game)
{
    this->game = game;
    setName("monster_specter");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_specter::update()
{
}

void Monster_specter::collision(Entity *other)
{
}

void Monster_specter::turn()
{
}

Monster_zombie::Monster_zombie(Game *game)
{
    this->game = game;
    setName("monster_zombie");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_zombie::update()
{
}

void Monster_zombie::collision(Entity *other)
{
}

void Monster_zombie::turn()
{
}

Monster_skeleton::Monster_skeleton(Game *game)
{
    this->game = game;
    setName("monster_skeleton");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_skeleton::update()
{
}

void Monster_skeleton::collision(Entity *other)
{
}

void Monster_skeleton::turn()
{
}

Monster_skeletonCaptain::Monster_skeletonCaptain(Game *game)
{
    this->game = game;
    setName("monster_skeletonCaptain");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_skeletonCaptain::update()
{
}

void Monster_skeletonCaptain::collision(Entity *other)
{
}

void Monster_skeletonCaptain::turn()
{
}

Monster_skeletonMage::Monster_skeletonMage(Game *game)
{
    this->game = game;
    setName("monster_skeletonMage");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_skeletonMage::update()
{
}

void Monster_skeletonMage::collision(Entity *other)
{
}

void Monster_skeletonMage::turn()
{
}

Monster_vampire::Monster_vampire(Game *game)
{
    this->game = game;
    setName("monster_vampire");
    setProperties(game->getObjectConfig(), getName());
}

void Monster_vampire::update()
{
}

void Monster_vampire::collision(Entity *other)
{
}

void Monster_vampire::turn()
{
}
}

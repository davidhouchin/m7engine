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
Monster::~Monster()
{
    game->killMonster(mId);
}

bool Monster::setProperties(ConfigReader *reader, std::string name)
{
    if (!reader->hasSection(name)) {
        return false;
    }

    longName = reader->getString(name, "longname", name);

    family = reader->getString(name, "family", "");

    resourceName = reader->getString(name, "sprite", "");
    if (resourceName != "") {
        setImage(ResourceManager::getInstance()->getSprite(resourceName.c_str()));
    }

    depth = reader->getInt(name, "depth", 0);

    width = reader->getInt(name, "width", 1);
    height = reader->getInt(name, "height", 1);

    xOffset = reader->getInt(name, "xoffset", 0);
    yOffset = reader->getInt(name, "yoffset", 0);

    xBBox = reader->getInt(name, "xbbox", 0);
    yBBox = reader->getInt(name, "ybbox", 0);
    bbox.w = reader->getInt(name, "wbbox", width);
    bbox.h = reader->getInt(name, "hbbox", height);

    scale = reader->getInt(name, "scale", 1);

    visible = reader->getBool(name, "visible", true);

    solid = reader->getBool(name, "solid", false);

    color.r = reader->getInt(name, "r", 255);
    color.g = reader->getInt(name, "g", 255);
    color.b = reader->getInt(name, "b", 255);
    color.a = reader->getInt(name, "a", 255);

    exp = reader->getInt(name, "exp", 0);
    hp = reader->getInt(name, "hp", 1);
    mp = reader->getInt(name, "mp", 1);
    minDamage = reader->getInt(name, "mindamage", 1);
    maxDamage = reader->getInt(name, "maxdamage", 1);
    defense = reader->getInt(name, "defense", 1);

    return true;
}

void Monster::alarm(int timerNum)
{
    if (timerNum == 0) {
        setAlpha(255);
    }
}

void Monster::turn()
{
    if (this->hp <= 0) {
        game->getLogger()->logMessage(0, "%s is dead.", longName.c_str());
        game->getEngine()->destroyEntity(this->getID());
    }
}

void Monster::die()
{
    game->getLogger()->logMessage(0, "%s is dead.", longName.c_str());
    game->getEngine()->destroyEntity(this->getID());
}

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
}

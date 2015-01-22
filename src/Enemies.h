/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Enemies
 *  Enemies.h
 *  Purpose: Enemy character classes.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#ifndef ENEMIES_H
#define ENEMIES_H

#include "engine/Entity.h"

using namespace M7engine;
namespace SampleGame {

class Game;

class EnemyH : public Entity {
private:
    Game *game;

public:
    EnemyH(Game *game);
    void update();
    void collision(Entity *other);
};

class EnemyV : public Entity {
private:
    Game *game;
public:
    EnemyV(Game *game);
    void update();
    void collision(Entity *other);

};
}

#endif

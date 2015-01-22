/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Props
 *  Props.h
 *  Purpose: Misc. objects classes.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#ifndef PROPS_H
#define PROPS_H

#include "engine/Entity.h"

using namespace M7engine;
namespace SampleGame {

class Game;

class Coin : public Entity {
private:
public:
    Coin(Game *game);
};

class Wall : public Entity {
private:
public:
    Wall(Game *game);
};

class Tree : public Entity {
private:
public:
    Tree(Game *game);
};

class Dirt : public Tile {
private:
public:
    Dirt(Game *game);
};
}

#endif

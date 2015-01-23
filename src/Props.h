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

class Floor_brick : public Tile {
private:
public:
    Floor_brick(Game *game);
};

class Floor_dirt : public Tile {
private:
public:
    Floor_dirt(Game *game);
};

class Floor_grass : public Tile {
private:
public:
    Floor_grass(Game *game);
};

class Wall_brick : public Entity {
private:
public:
    Wall_brick(Game *game);
};
}

#endif

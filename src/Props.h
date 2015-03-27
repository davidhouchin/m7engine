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
#include "Items.h"

using namespace M7engine;
namespace SampleGame {

class Game;

class ItemProp : public Entity {
private:
    Item *item;

    enum itemObject {
        eSword, eSword2,
        eArmorBoots, eArmorChest, eArmorGloves, eArmorHelm,
        eCoins, eKey, ePotion,
        eNone
    };

    ItemProp::itemObject translateString(std::string const& str);

public:
    ItemProp(Game *game);
    ItemProp(Game *game, std::string name);

    Item* getItem() { return item; }
};

class Floor_brick : public Tile {
private:
public:
    Floor_brick(Game *game);
};

class Floor_brickVines : public Tile {
private:
public:
    Floor_brickVines(Game *game);
};

class Floor_brickMold : public Tile {
private:
public:
    Floor_brickMold(Game *game);
};

class Floor_water : public Tile {
private:
public:
    Floor_water(Game *game);
};

class Floor_water2 : public Tile {
private:
public:
    Floor_water2(Game *game);
};

class Floor_lava : public Tile {
private:
public:
    Floor_lava(Game *game);
};

class Floor_lava2 : public Tile {
private:
public:
    Floor_lava2(Game *game);
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

class Wall_brickVines : public Entity {
private:
public:
    Wall_brickVines(Game *game);
};

class Wall_brickMold : public Entity {
private:
public:
    Wall_brickMold(Game *game);
};

class Wall_brickStairsDown : public Entity {
private:
public:
    Wall_brickStairsDown(Game *game);
};

class Wall_brickStairsUp : public Entity {
private:
public:
    Wall_brickStairsUp(Game *game);
};

class Wall_brickDoorClosed : public Entity {
private:
    bool locked;
public:
    Wall_brickDoorClosed(Game *game);
    bool getLocked() { return locked; }
    void setLocked(bool lock) { this->locked = lock; }
};

class Wall_brickDoorOpen : public Entity {
private:
public:
    Wall_brickDoorOpen(Game *game);
};

class Wall_brickGateClosed : public Entity {
private:
    bool locked;
public:
    Wall_brickGateClosed(Game *game);
    bool getLocked() { return locked; }
    void setLocked(bool lock) { this->locked = lock; }
};

class Wall_brickGateOpen : public Entity {
private:
public:
    Wall_brickGateOpen(Game *game);
};

class Wall_brickGrate : public Entity {
private:
public:
    Wall_brickGrate(Game *game);
};
}

#endif

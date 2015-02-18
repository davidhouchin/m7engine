/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Player
 *  Player.h
 *  Purpose: Player character class.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "engine/Entity.h"
#include "Items.h"

using namespace M7engine;
namespace SampleGame {

class Game;

class Player : public Entity {
private:
    int speed, runSpeed, runDelay, runCounter, runDelayCounter;
    bool dead, notStarted, running, moved;
    int startx, starty, moves;

    int level, exp, hp, mp, strength, intellect, dexterity;
    int attack, defense, weight, weightCapacity;

    Item *headArmor, *torsoArmor, *legArmor, *footArmor, *weapon;

    std::vector<Item*> inventory;

    std::string name;

    Game *game;
    
public:
    Player(Game *game);
    
    void update();
    void collision(Entity *other);
    void alarm(int timerNum);

    void addItem(Item *item);
    void removeItem(std::string name);
    void equipItem(std::string name);
    void unequipItem(std::string name);
    void displayInventory();

    Item* getInventoryItem(std::string name);

};
}

#endif

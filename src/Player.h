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
#include "Enemies.h"
#include "Props.h"

using namespace M7engine;
namespace SampleGame {

class Game;
class StatusBar;

class Player : public Entity {
friend class StatusBar;
friend class InventoryWindow;

private:
    int speed, runSpeed, runDelay, runCounter, runDelayCounter;
    bool dead, notStarted, running, moved;
    int startx, starty, moves;

    int level, exp, hp, hpMax, mp, mpMax, strength, intellect, dexterity;
    int damage, defense, weight, weightCapacity;

    Item *headArmor, *torsoArmor, *handArmor, *footArmor, *weapon;

    std::vector<Item*> inventory;

    std::string name;

    StatusBar *statusBar;

    Game *game;
    
public:
    Player(Game *game);
    virtual ~Player();
    
    void update();
    void collision(Entity *other);
    void alarm(int timerNum);

    void attack(Monster *target);
    void open(Entity *door);

    bool addItem(Item *item);
    void dropItem(std::string name);
    void removeItem(std::string name, int number);
    void equipItem(std::string name);
    void unequipItem(std::string name);
    void useItem(std::string name);
    void displayInventory();

    Item* getInventoryItem(std::string name);

    StatusBar* getStatusBar() { return this->statusBar; }

};
}

#endif

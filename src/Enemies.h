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

class Monster : public Entity {
protected:
    std::string longName;
    int mId;
    int exp, hp, mp;
    int minDamage, maxDamage, defense;

public:
    Monster() {}
    ~Monster();
    virtual void update() {}
    virtual void collision(Entity *other) {}
    virtual void turn();
    virtual void alarm(int timerNum);
    virtual void die();

    bool setProperties(ConfigReader *reader, std::string name);

    int getDefense() { return this->defense; }

    void setHp(int hp) { this->hp = hp; }
    int getHp() { return this->hp; }

    int getExp() { return this->exp; }

    void setMonsterID(int id) { this->mId = id; }
    int getMonsterID() { return this->mId; }

    std::string getLongName() { return this->longName; }

    Game *game;
};

class Monster_ghost : public Monster {
public:
    Monster_ghost(Game *game);
    void update();
    void collision(Entity *other);
};

class Monster_wraith : public Monster {
public:
    Monster_wraith(Game *game);
    void update();
    void collision(Entity *other);
};

class Monster_specter : public Monster {
public:
    Monster_specter(Game *game);
    void update();
    void collision(Entity *other);
};

class Monster_zombie : public Monster {
public:
    Monster_zombie(Game *game);
    void update();
    void collision(Entity *other);
};

class Monster_skeleton : public Monster {
public:
    Monster_skeleton(Game *game);
    void update();
    void collision(Entity *other);
    void turn();
};

class Monster_skeletonCaptain : public Monster {
public:
    Monster_skeletonCaptain(Game *game);
    void update();
    void collision(Entity *other);
};

class Monster_skeletonMage : public Monster {
public:
    Monster_skeletonMage(Game *game);
    void update();
    void collision(Entity *other);
};

class Monster_vampire : public Monster {
public:
    Monster_vampire(Game *game);
    void update();
    void collision(Entity *other);
};
}

#endif

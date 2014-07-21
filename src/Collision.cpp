/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Collision Manager
 *  CollisionManager.cpp
 *  Purpose: Determines if two entities are colliding.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Collision.h"
#include "M7engine.h"

namespace M7engine {
CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}

bool CollisionManager::getIntersect(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

bool CollisionManager::getCollisionBBox(Entity *a, Entity *b)
{
    SDL_Rect rA, rB;

    rA.x = a->getX();
    rA.w = a->getWidth();
    rA.y = a->getY();
    rA.h = a->getHeight();

    rB.x = b->getX();
    rB.w = b->getWidth();
    rB.y = b->getY();
    rB.h = b->getHeight();

    if (getIntersect(rA, rB)) {
        return true;
    } else {
        return false;
    }
}

bool CollisionManager::getPlaceMeeting(int x, int y, Entity *entity)
{
    return false;
}

bool CollisionManager::getPlaceMeetingInstance(int x, int y, int idA, int idB)
{
    SDL_Rect rA, rB;
    Entity *eA = Engine::getInstance()->findEntity(idA);
    Entity *eB = Engine::getInstance()->findEntity(idB);

    rA.x = x - eA->getXOffset();
    rA.w = eA->getWidth();
    rA.y = y - eA->getYOffset();
    rA.h = eA->getHeight();

    rB.x = eB->getX()-eB->getXOffset();
    rB.w = eB->getWidth();
    rB.y = eB->getY()-eB->getYOffset();
    rB.h = eB->getHeight();

    if (getIntersect(rA, rB)) {
        return true;
    } else {
        return false;
    }
}

bool CollisionManager::getPointMeetingInstance(int x, int y, int id)
{
    SDL_Rect rA, rB;
    Entity *e = Engine::getInstance()->findEntity(id);

    rA.x = e->getX();
    rA.w = e->getWidth();
    rA.y = e->getY();
    rA.h = e->getHeight();

    rB.x = x;
    rB.w = 1;
    rB.y = y;
    rB.h = 1;

    if (getIntersect(rA, rB)) {
        return true;
    } else {
        return false;
    }
}
}

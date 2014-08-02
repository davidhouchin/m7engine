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
CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
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

bool CollisionManager::getPlaceMeetingObject(int x, int y, int id, std::string name)
{
    SDL_Rect rA, rB;
    Entity *eA = Engine::getInstance()->findEntity(id);
    rA.x = x;
    rA.w = eA->getWBBox();
    rA.y = y;
    rA.h = eA->getHBBox();

    std::vector<Entity*> entities = Engine::getInstance()->getEntityList();
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getName() == name) {
            rB.x = entity->getXBBox();
            rB.w = entity->getWBBox();
            rB.y = entity->getYBBox();
            rB.h = entity->getHBBox();

            if (getIntersect(rA, rB)) {
                return true;
            }
        }
        iter++;
    }

    return false;
}

bool CollisionManager::getPlaceMeetingInstance(int x, int y, int idA, int idB)
{
    SDL_Rect rA, rB;
    Entity *eA = Engine::getInstance()->findEntity(idA);
    Entity *eB = Engine::getInstance()->findEntity(idB);

    rA.x = x;
    rA.w = eA->getWBBox();
    rA.y = y;
    rA.h = eA->getHBBox();

    rB.x = eB->getXBBox();
    rB.w = eB->getWBBox();
    rB.y = eB->getYBBox();
    rB.h = eB->getHBBox();

    if (getIntersect(rA, rB)) {
        return true;
    } else {
        return false;
    }
}

bool CollisionManager::getPlaceMeetingSolid(int x, int y, int id)
{
    SDL_Rect rA, rB;
    Entity *eA = Engine::getInstance()->findEntity(id);
    rA.x = x;
    rA.w = eA->getWBBox();
    rA.y = y;
    rA.h = eA->getHBBox();
    //drawRectangle(rA.x, rA.y, rA.w, rA.h, 255, 0, 0, 255);

    std::vector<Entity*> entities = Engine::getInstance()->getEntityList();
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getSolid()) {
            rB.x = entity->getXBBox();
            rB.w = entity->getWBBox();
            rB.y = entity->getYBBox();
            rB.h = entity->getHBBox();
            //drawRectangle(rB.x, rB.y, rB.w, rB.h, 255, 0, 0, 255);

            if (getIntersect(rA, rB)) {
                return true;
            }
        }
        iter++;
    }

    return false;
}

bool CollisionManager::getPointMeetingInstance(int x, int y, int id)
{
    SDL_Rect rA, rB;
    Entity *e = Engine::getInstance()->findEntity(id);

    rA.x = e->getXBBox();
    rA.w = e->getWBBox();
    rA.y = e->getYBBox();
    rA.h = e->getHBBox();

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

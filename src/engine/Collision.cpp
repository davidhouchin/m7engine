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

bool CollisionManager::getPlaceMeetingObject(int id, std::string name)
{
    SDL_Rect rA, rB;
    Entity *eA = Engine::getInstance()->findEntity(id);
    rA = eA->getBBox();

    std::vector<Entity*> entities = Engine::getInstance()->getEntityList();
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getName() == name) {
            rB = entity->getBBox();

            if (getIntersect(rA, rB)) {
                return true;
            }
        }
        iter++;
    }

    return false;
}

bool CollisionManager::getPlaceMeetingFamily(int id, std::string family)
{
    SDL_Rect rA, rB;
    Entity *eA = Engine::getInstance()->findEntity(id);
    rA.x = eA->getXBBox();
    rA.w = eA->getWBBox();
    rA.y = eA->getYBBox();
    rA.h = eA->getHBBox();

    std::vector<Entity*> entities = Engine::getInstance()->getEntityList();
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getFamily() == family) {
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

    rB = eB->getBBox();

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

    std::vector<Entity*> entities = Engine::getInstance()->getEntityList();
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        if (entity->getSolid()) {
            rB = entity->getBBox();

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

    rA = e->getBBox();

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

Entity* CollisionManager::getPointMeetingEntity(int x, int y)
{
    SDL_Rect rA, rB;
    rA.x = x;
    rA.w = 1;
    rA.y = y;
    rA.h = 1;

    std::vector<Entity*> entities = Engine::getInstance()->getEntityList();
    std::vector<Entity*>::iterator iter;
    Entity *entity;
    iter = entities.begin();

    while (iter != entities.end()) {
        entity = *iter;
        rB = entity->getBBox();

        if (getIntersect(rA, rB)) {
            return entity;
        }
        iter++;
    }

    return NULL;
}

Tile* CollisionManager::getPointMeetingTile(int x, int y, int gridSize)
{
    SDL_Rect rA, rB;
    rA.x = x;
    rA.w = 1;
    rA.y = y;
    rA.h = 1;

    std::vector<Tile*> tiles = Engine::getInstance()->getTileList();
    std::vector<Tile*>::iterator iter;
    Tile *tile;
    iter = tiles.begin();

    while (iter != tiles.end()) {
        tile = *iter;
        rB.x = tile->getX();
        rB.w = gridSize;
        rB.y = tile->getY();
        rB.h = gridSize;

        if (getIntersect(rA, rB)) {
            return tile;
        }
        iter++;
    }

    return NULL;
}

int CollisionManager::getDistanceBetweenEntities(Entity *a, Entity *b)
{
    Vector2 posA = a->getPosition();
    Vector2 posB = b->getPosition();

    return posA.distance(posB);
}
}

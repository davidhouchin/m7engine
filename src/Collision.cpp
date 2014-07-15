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

namespace M7engine {
CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}

bool CollisionManager::getCollisionBBox(Entity *a, Entity *b) {
    int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

    leftA = a->getX();
    rightA = a->getX() + a->getWidth();
    topA = a->getY();
    bottomA = a->getY() + a->getHeight();

    leftB = b->getX();
    rightB = b->getX() + b->getWidth();
    topB = b->getY();
    bottomB = b->getY() + b->getHeight();

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
}

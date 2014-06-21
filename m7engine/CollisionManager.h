/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Collision Manager
 *  CollisionManager.h
 *  Purpose: Determines if two entities are colliding.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef COLLISIONMANAGER_H
#define	COLLISIONMANAGER_H

#include "Entity.h"
#include "Logger.h"

namespace M7engine {
class CollisionManager {
public:
    CollisionManager();
    virtual ~CollisionManager();

    /**
     *  Tests if the bounding boxes of two entities collide.
     *  @param *a First entity to test.
     *  @param *b Second entity to test.
     *  @return A bool determining if the two entities collide.
     */
    bool getCollisionBBox(Entity *a, Entity *b);

private:
};
}
#endif

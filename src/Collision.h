/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
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

#include <SDL2/SDL.h>

#include "Entity.h"
#include "Logger.h"

namespace M7engine {
class CollisionManager {
public:
    CollisionManager();
    virtual ~CollisionManager();

    /**
     *  Tests if two rects are intersecting.
     *  @param a First rect to test.
     *  @param b Second rect to test.
     *  @return A bool determining if the two rects intersect.
     */
    bool getIntersect(SDL_Rect a, SDL_Rect b);

    /**
     *  Tests if the bounding boxes of two entities collide.
     *  @param *a First entity to test.
     *  @param *b Second entity to test.
     *  @return A bool determining if the two entities collide.
     */
    bool getCollisionBBox(Entity *a, Entity *b);

    /**
     *  Tests if any instance of passed object is colliding with point.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *  @param *entity Type of entity to check.
     *  @return A bool determining if the entity is at the position.
     */
    bool getPlaceMeeting(int x, int y, Entity *entity);

    /**
     *  Tests if first entity is colliding with the second using an offset.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *
     *  @param idB ID of instance to check.
     *  @return A bool determining if the entity is at the position.
     */
    bool getPlaceMeetingInstance(int x, int y, int idA, int idB);

    /**
     *  Tests if a specific entity is colliding with point.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *  @param id ID of instance to check.
     *  @return A bool determining if the entity is at the position.
     */
    bool getPointMeetingInstance(int x, int y, int id);

private:
};
}
#endif

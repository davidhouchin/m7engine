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
     *  @brief Tests if two rects are intersecting.
     *  @param a First rect to test.
     *  @param b Second rect to test.
     *  @return A bool determining if the two rects intersect.
     */
    bool getIntersect(SDL_Rect a, SDL_Rect b);

    /**
     *  @brief Tests if the bounding boxes of two entities collide.
     *  @param *a First entity to test.
     *  @param *b Second entity to test.
     *  @return A bool determining if the two entities collide.
     */
    bool getCollisionBBox(Entity *a, Entity *b);

    /**
     *  @brief Tests if any instance of passed name is colliding with instance of given ID.
     *  @param id ID of instance to check from.
     *  @param name Name of instance to check collision with.
     *  @return A bool determining if the entity with given name is at the position.
     */
    bool getPlaceMeetingObject(int id, std::string name);

    /**
     *  @brief Tests if any instance of passed family is colliding with instance of given ID.
     *  @param id ID of instance to check from.
     *  @param *family Name of instance family to check collision with.
     *  @return A bool determining if the entity with given family is at the position.
     */
    bool getPlaceMeetingFamily(int id, std::string family);

    /**
     *  @brief Tests if first entity is colliding with the second using an offset.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *  @param idA ID of first entity to check.
     *  @param idB ID of second entity to check.
     *  @return A bool determining if the entity is at the position.
     */
    bool getPlaceMeetingInstance(int x, int y, int idA, int idB);

    /**
     *  @brief Tests if an entity is colliding with a solid object.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *  @param id ID of entity to check.
     *  @return A bool determining if the entity is colliding with a solid entity.
     */
    bool getPlaceMeetingSolid(int x, int y, int id);

    /**
     *  @brief Tests if a specific entity is colliding with point.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *  @param id ID of instance to check.
     *  @return A bool determining if the entity is at the position.
     */
    bool getPointMeetingInstance(int x, int y, int id);

    /**
     *  @brief Returns a pointer to the entity found at an XY position. Returns NULL if no entity is found.
     *  @param x X coordinate to check.
     *  @param y Y coordinate to check.
     *  @return A pointer if an entity is found, otherwise NULL.
     */
    Entity* getPointMeetingEntity(int x, int y);

    /**
     *  @brief Returns a pointer to the tile found at an XY position, with gridSize determining the assumed width and height. Returns NULL if no tile is found.
     *  @param x
     *  @param y
     *  @param gridSize
     *  @return A pointer if a tile is found, otherwise NULL.
     */
    Tile* getPointMeetingTile(int x, int y, int gridSize);

private:
};
}
#endif

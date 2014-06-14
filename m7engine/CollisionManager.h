/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably 
* don't even want.. It is made available to you under the terms of 
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef COLLISIONMANAGER_H
#define	COLLISIONMANAGER_H

#include "Entity.h"
#include "Logger.h"

namespace M7engine
{
class CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager();

	bool getCollisionBBox(Entity *a, Entity *b);

private:
};
}
#endif

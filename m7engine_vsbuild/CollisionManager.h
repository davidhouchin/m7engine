#ifndef COLLISIONMANAGER_H
#define	COLLISIONMANAGER_H

#include "Entity.h"

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

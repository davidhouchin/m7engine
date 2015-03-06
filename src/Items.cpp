/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Items
 *  Items.cpp
 *  Purpose: Usable items class.
 *  @author David Houchin
 *  @version 1.0 2/17/15
 */

#include "Items.h"

namespace SampleGame {
Item_sword::Item_sword()
{
    this->name = "sword";
    description = "A rusty sword.";
    equipped = false;
    itemType = weapon;
    minDamage = 10;
    maxDamage = 25;
    weight = 10;
    cost = 5;
}
}

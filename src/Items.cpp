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
    weaponType = sword;
    minDamage = 10;
    maxDamage = 25;
    weight = 10;
    cost = 15;
}

Item_sword2::Item_sword2()
{
    this->name = "sword_flame";
    description = "A flaming sword. Cool.";
    equipped = false;
    itemType = weapon;
    weaponType = sword;
    minDamage = 50;
    maxDamage = 65;
    weight = 10;
    cost = 100;
}

Item_armorBoots::Item_armorBoots()
{
    this->name = "armor_boots";
    description = "A set of iron boots.";
    equipped = false;
    itemType = armor;
    armorType = foot;
    armorAmount = 5;
    weight = 10;
    cost = 10;
}

Item_armorChest::Item_armorChest()
{
    this->name = "armor_chest";
    description = "An iron breastplate.";
    equipped = false;
    itemType = armor;
    armorType = torso;
    armorAmount = 10;
    weight = 30;
    cost = 30;
}

Item_armorGloves::Item_armorGloves()
{
    this->name = "armor_gloves";
    description = "A pair of iron gauntlets.";
    equipped = false;
    itemType = armor;
    armorType = hand;
    armorAmount = 5;
    weight = 5;
    cost = 10;
}

Item_armorHelm::Item_armorHelm()
{
    this->name = "armor_helm";
    description = "An iron helmet.";
    equipped = false;
    itemType = armor;
    armorType = head;
    armorAmount = 10;
    weight = 10;
    cost = 15;
}

Item_coins::Item_coins()
{
    this->name = "coins";
    description = "A bunch of gold coins.";
    equipped = false;
    itemType = item;
    weight = 0;
    cost = 10;
}

Item_key::Item_key()
{
    this->name = "key";
    description = "A hefty metal key.";
    equipped = false;
    itemType = item;
    weight = 1;
    cost = 0;
}

Item_potion::Item_potion()
{
    this->name = "potion";
    description = "A strange red liquid.";
    equipped = false;
    itemType = item;
    weight = 3;
    cost = 50;
}
}

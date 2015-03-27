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
    longName = "Rusty Sword";
    description = "A rusty sword.";
    imageName = "item_sword";
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
    longName = "Flaming Sword";
    description = "A flaming sword. Cool.";
    imageName = "item_sword2";
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
    longName = "Iron Boots";
    description = "A set of iron boots.";
    imageName = "item_armorboots";
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
    longName = "Iron Breastplate";
    description = "An iron breastplate.";
    imageName = "item_armorchest";
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
    longName = "Iron Gauntlets";
    description = "A pair of iron gauntlets.";
    imageName = "item_armorgloves";
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
    longName = "Iron Helm";
    description = "An iron helmet.";
    imageName = "item_armorhelm";
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
    longName = "Stack of coins";
    description = "A bunch of gold coins.";
    imageName = "item_coins";
    equipped = false;
    itemType = item;
    weight = 0;
    cost = 10;
}

Item_key::Item_key()
{
    this->name = "key";
    longName = "Iron Key";
    description = "A hefty metal key.";
    imageName = "item_key";
    equipped = false;
    itemType = item;
    weight = 1;
    cost = 0;
}

Item_potion::Item_potion()
{
    this->name = "potion";
    longName = "Red Potion";
    description = "A strange red liquid.";
    imageName = "item_potion";
    equipped = false;
    itemType = item;
    weight = 3;
    cost = 50;
}
}

/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Items
 *  Items.h
 *  Purpose: Usable items class.
 *  @author David Houchin
 *  @version 1.0 2/17/15
 */

#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>

namespace SampleGame {

class Item {
public:
    Item() {}

    std::string getName() { return this->name; }
    std::string getDescription() { return this->description; }
    bool getEquipped() { return this->equipped; }
    void setEquipped(bool equipped) { this->equipped = equipped; }
    int getArmor() { return this->armorAmount; }
    int getMinDamage() { return this->minDamage; }
    int getMaxDamage() { return this->maxDamage; }
    int getWeight() { return this->weight; }
    int getCost() { return this->cost; }

    enum itemClass {
        item, armor, weapon
    };

    enum armorClass {
        head, torso, leg, foot
    };

    enum weaponClass {
        sword, bow, wand
    };

    itemClass getItemClass() { return this->itemType; }
    armorClass getArmorClass() { return this->armorType; }
    weaponClass getWeaponClass() { return this->weaponType; }

protected:
    std::string name, description;
    bool equipped;
    int armorAmount, minDamage, maxDamage, weight, cost;

    itemClass itemType;
    armorClass armorType;
    weaponClass weaponType;

};

class Item_sword : public Item {
public:
    Item_sword();
};

}

#endif

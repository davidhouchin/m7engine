/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Props
 *  Props.cpp
 *  Purpose: Misc. objects classes.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#include "Props.h"
#include "Game.h"

namespace SampleGame {
ItemProp::ItemProp(Game *game)
{
    setName("itemprop");
    setProperties(game->getObjectConfig(), getName());

    int rand = randomRangeInt(0, 8);

    switch (rand) {
        case 0: item = new Item_sword(); image = game->getResourceManager()->getSprite("item_sword"); break;
        case 1: item = new Item_armorBoots(); image = game->getResourceManager()->getSprite("item_armorboots"); break;
        case 2: item = new Item_armorChest(); image = game->getResourceManager()->getSprite("item_armorchest"); break;
        case 3: item = new Item_armorGloves(); image = game->getResourceManager()->getSprite("item_armorgloves"); break;
        case 4: item = new Item_armorHelm(); image = game->getResourceManager()->getSprite("item_armorhelm"); break;
        case 5: item = new Item_coins(); image = game->getResourceManager()->getSprite("item_coins"); break;
        case 6: item = new Item_key(); image = game->getResourceManager()->getSprite("item_key"); break;
        case 7: item = new Item_potion(); image = game->getResourceManager()->getSprite("item_potion"); break;
        case 8: item = new Item_sword2(); image = game->getResourceManager()->getSprite("item_sword2"); break;
    }
}

ItemProp::ItemProp(Game *game, std::string name)
{
    setName("itemprop");
    setProperties(game->getObjectConfig(), getName());

    switch (translateString(name)) {
        case eSword: item = new Item_sword(); image = game->getResourceManager()->getSprite("item_sword"); break;
        case eArmorBoots: item = new Item_armorBoots(); image = game->getResourceManager()->getSprite("item_armorboots"); break;
        case eArmorChest: item = new Item_armorChest(); image = game->getResourceManager()->getSprite("item_armorchest"); break;
        case eArmorGloves: item = new Item_armorGloves(); image = game->getResourceManager()->getSprite("item_armorgloves"); break;
        case eArmorHelm: item = new Item_armorHelm(); image = game->getResourceManager()->getSprite("item_armorhelm"); break;
        case eCoins: item = new Item_coins(); image = game->getResourceManager()->getSprite("item_coins"); break;
        case eKey: item = new Item_key(); image = game->getResourceManager()->getSprite("item_key"); break;
        case ePotion: item = new Item_potion(); image = game->getResourceManager()->getSprite("item_potion"); break;
        case eSword2: item = new Item_sword2(); image = game->getResourceManager()->getSprite("item_sword2"); break;
    }
}

ItemProp::itemObject ItemProp::translateString(std::string const& str)
{
    if (str == "sword") return eSword;
    else if (str == "sword_flame") return eSword2;
    else if (str == "armor_boots") return eArmorBoots;
    else if (str == "armor_chest") return eArmorChest;
    else if (str == "armor_gloves") return eArmorGloves;
    else if (str == "armor_helm") return eArmorHelm;
    else if (str == "coins") return eCoins;
    else if (str == "key") return eKey;
    else if (str == "potion") return ePotion;
    else return eNone;
}

Floor_brick::Floor_brick(Game *game)
{
    setName("floor_brick");
    setProperties(game->getObjectConfig(), getName());
}

Floor_brickVines::Floor_brickVines(Game *game)
{
    setName("floor_brickVines");
    setProperties(game->getObjectConfig(), getName());
}

Floor_brickMold::Floor_brickMold(Game *game)
{
    setName("floor_brickMold");
    setProperties(game->getObjectConfig(), getName());
}

Floor_dirt::Floor_dirt(Game *game)
{
    setName("floor_dirt");
    setProperties(game->getObjectConfig(), getName());
}

Floor_grass::Floor_grass(Game *game)
{
    setName("floor_grass");
    setProperties(game->getObjectConfig(), getName());
}

Floor_water::Floor_water(Game *game)
{
    setName("floor_water");
    setProperties(game->getObjectConfig(), getName());
}

Floor_water2::Floor_water2(Game *game)
{
    setName("floor_water2");
    setProperties(game->getObjectConfig(), getName());
}

Floor_lava::Floor_lava(Game *game)
{
    setName("floor_lava");
    setProperties(game->getObjectConfig(), getName());
}

Floor_lava2::Floor_lava2(Game *game)
{
    setName("floor_lava2");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brick::Wall_brick(Game *game)
{
    setName("wall_brick");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickVines::Wall_brickVines(Game *game)
{
    setName("wall_brickVines");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickMold::Wall_brickMold(Game *game)
{
    setName("wall_brickMold");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickStairsDown::Wall_brickStairsDown(Game *game)
{
    setName("wall_brickStairsDown");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickStairsUp::Wall_brickStairsUp(Game *game)
{
    setName("wall_brickStairsUp");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickDoorClosed::Wall_brickDoorClosed(Game *game)
{
    setName("wall_brickDoorClosed");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickDoorOpen::Wall_brickDoorOpen(Game *game)
{
    setName("wall_brickDoorOpen");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickGateClosed::Wall_brickGateClosed(Game *game)
{
    setName("wall_brickGateClosed");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickGateOpen::Wall_brickGateOpen(Game *game)
{
    setName("wall_brickGateOpen");
    setProperties(game->getObjectConfig(), getName());
}

Wall_brickGrate::Wall_brickGrate(Game *game)
{
    setName("wall_brickGrate");
    setProperties(game->getObjectConfig(), getName());
}
}

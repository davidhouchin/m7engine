/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Level
 *  Level.cpp
 *  Purpose: Main level class.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#include "Level.h"

namespace SampleGame {
Level::Level(Game *game)
{
    this->game = game;
    width = 0;
    height = 0;
}

Level::mapObject Level::translateString(std::string const& str)
{
    if (str == "width") return eWidth;
    else if (str == "height") return eHeight;
    else if (str == "player") return ePlayer;
    else if (str == "itemprop") return eItem;
    else if (str == "monster_ghost") return eMonster_ghost;
    else if (str == "monster_wraith") return eMonster_wraith;
    else if (str == "monster_specter") return eMonster_specter;
    else if (str == "monster_zombie") return eMonster_zombie;
    else if (str == "monster_skeleton") return eMonster_skeleton;
    else if (str == "monster_skeletonCaptain") return eMonster_skeletonCaptain;
    else if (str == "monster_skeletonMage") return eMonster_skeletonMage;
    else if (str == "monster_vampire") return eMonster_vampire;
    else if (str == "floor_brick") return eFloor_brick;
    else if (str == "floor_brickVines") return eFloor_brickVines;
    else if (str == "floor_brickMold") return eFloor_brickMold;
    else if (str == "floor_dirt") return eFloor_dirt;
    else if (str == "floor_grass") return eFloor_grass;
    else if (str == "floor_water") return eFloor_water;
    else if (str == "floor_water2") return eFloor_water2;
    else if (str == "floor_lava") return eFloor_lava;
    else if (str == "floor_lava2") return eFloor_lava2;
    else if (str == "wall_brick") return eWall_brick;
    else if (str == "wall_brickVines") return eWall_brickVines;
    else if (str == "wall_brickMold") return eWall_brickMold;
    else if (str == "wall_brickStairsDown") return eWall_brickStairsDown;
    else if (str == "wall_brickStairsUp") return eWall_brickStairsUp;
    else if (str == "wall_brickDoorClosed") return eWall_brickDoorClosed;
    else if (str == "wall_brickDoorOpen") return eWall_brickDoorOpen;
    else if (str == "wall_brickGateClosed") return eWall_brickGateClosed;
    else if (str == "wall_brickGateOpen") return eWall_brickGateOpen;
    else if (str == "wall_brickGrate") return eWall_brickGrate;
    else return eNone;
}

bool Level::load(std::string filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        game->getLogger()->logError(0, "Failed to load level '%s'", filename.c_str());
        return false;
    }

    game->getEngine()->destroyAllEntities();
    game->getEngine()->destroyAllTiles();

    Entity *entity;
    Tile *tile;
    Monster *monster;

    bool isMonster = false;

    while (!file.eof()) {
        std::vector<std::string> input;
        std::string line;
        std::getline(file, line, '\n');

        if (line[0] == '#') {
            continue;
        }

        if (line.length() > 0) {
            input = chunkify(line, ' ');

            switch (translateString(input[0])) {
            case eWidth: width = stringToInt(input[1]); break;
            case eHeight: height = stringToInt(input[1]); break;

            case ePlayer: entity = new Player(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;

            case eItem: entity = new ItemProp(game, input[3]);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;

            case eMonster_ghost: monster = new Monster_ghost(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_wraith: monster = new Monster_wraith(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_specter: monster = new Monster_specter(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_zombie: monster = new Monster_zombie(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_skeleton: monster = new Monster_skeleton(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_skeletonCaptain: monster = new Monster_skeletonCaptain(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_skeletonMage: monster = new Monster_skeletonMage(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eMonster_vampire: monster = new Monster_vampire(game); isMonster = true;
                monster->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;

            case eFloor_brick: tile = new Floor_brick(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_brickVines: tile = new Floor_brickVines(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_brickMold: tile = new Floor_brickMold(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_dirt: tile = new Floor_dirt(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_grass: tile = new Floor_grass(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_water: tile = new Floor_water(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_water2: tile = new Floor_water2(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_lava: tile = new Floor_lava(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eFloor_lava2: tile = new Floor_lava2(game);
                tile->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;

            case eWall_brick: entity = new Wall_brick(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickVines: entity = new Wall_brickVines(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickMold: entity = new Wall_brickMold(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickStairsDown: entity = new Wall_brickStairsDown(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickStairsUp: entity = new Wall_brickStairsUp(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickDoorClosed: entity = new Wall_brickDoorClosed(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickDoorOpen: entity = new Wall_brickDoorOpen(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickGateClosed: entity = new Wall_brickGateClosed(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickGateOpen: entity = new Wall_brickGateOpen(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            case eWall_brickGrate: entity = new Wall_brickGrate(game);
                entity->setPosition(stringToInt(input[1]), stringToInt(input[2])); break;
            default: break;
            }
        }

        if (isMonster) {
            game->addMonster(monster);
            isMonster = false;
        }

        continue;
    }

    game->getEngine()->sortEntitiesByDepth();
    game->getEngine()->sortTilesByDepth();

    game->getLogger()->logMessage(0, "Loaded level '%s'", filename.c_str());

    return true;
}
}

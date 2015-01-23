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
    interval = 0;
    width = 0;
    height = 0;
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

    int xx, yy;
    xx = 0;
    yy = 0;

    Entity *entity;
    Tile *tile;

    while (!file.eof()) {
        std::string line;
        std::getline(file, line, '\n');

        if (line[0] == '#') {
            continue;
        }

        if (line[0] == 's') {
            interval = stringToInt(split(line, ':').back());
            yy = interval;
            continue;
        }

        if (line[0] == 'w') {
            width = stringToInt(split(line, ':').back());
            continue;
        }

        if (line[0] == 'h') {
            height = stringToInt(split(line, ':').back());
            continue;
        }

        switch (stringToInt(line)) {
        case 1: entity = new Player(game); entity->setPosition(xx, yy); break;
        case 2: entity = new Monster_skeleton(game); entity->setPosition(xx, yy); break;
        case 3: entity = new Wall_brick(game); entity->setPosition(xx, yy); break;
        case 4: tile = new Floor_dirt(game); entity->setPosition(xx, yy); break;
        case 5: tile = new Floor_brick(game); tile->setPosition(xx, yy); break;
        case 6: tile = new Floor_grass(game); entity->setPosition(xx, yy); break;
        default: break;
        }

        xx += interval;
        if (xx >= width) {
            xx = 0; yy += interval;
        }

        continue;
    }

    game->getEngine()->sortEntitiesByDepth();
    game->getEngine()->sortTilesByDepth();

    game->getLogger()->logMessage(0, "Loaded level '%s'", filename.c_str());

    return true;
}
}

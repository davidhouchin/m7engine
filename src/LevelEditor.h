/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  LevelEditor
 *  LevelEditor.h
 *  Purpose: Main level editor class.
 *  @author David Houchin
 *  @version 1.0 1/24/15
 */

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "Game.h"
#include "Level.h"

namespace SampleGame {
class LevelEditor : public Window {
private:
    Game *game;
    Label *objLabel, *lvlLabel, *clearLabel, *resLabel;
    DropDownList *objDropDownList;
    TextBox *lvlTextBox, *widthTextBox, *heightTextBox;
    Button *saveButton, *loadButton, *clearButton, *resButton;

    int gridSize;

    bool drawGrid, drawSquare, hasDeletedEntity;

    SDL_Color gridColor, squareColor;

    std::ofstream saveFile;
    const char* filename;

    Entity *newEntity;
    Entity *deleteEntity;
    Monster *newMonster;
    Tile *newTile;
    Tile *deleteTile;

    enum mapObject {
        eWidth, eHeight,
        ePlayer,
        eMonster_ghost, eMonster_wraith, eMonster_specter, eMonster_zombie,
        eMonster_skeleton, eMonster_skeletonCaptain, eMonster_skeletonMage,
        eMonster_vampire,
        eFloor_brick, eFloor_brickVines, eFloor_brickMold, eFloor_dirt,
        eFloor_grass, eFloor_water, eFloor_water2, eFloor_lava, eFloor_lava2,
        eWall_brick, eWall_brickVines, eWall_brickMold, eWall_brickStairsDown,
        eWall_brickStairsUp, eWall_brickDoorClosed, eWall_brickDoorOpen,
        eWall_brickGateClosed, eWall_brickGateOpen, eWall_brickGrate,
        eNone
    };

    mapObject selectedObject;

    LevelEditor::mapObject translateString(std::string const& str);
    void addObjectsToDropDownList();

public:
    LevelEditor(Game *game, int x, int y, int width, int height);
    void handleInput(Widget *widget);
    void draw();
    void update();

    bool save(const char* file);
};
}

#endif

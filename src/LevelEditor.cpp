/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  LevelEditor
 *  LevelEditor.cpp
 *  Purpose: Main level editor class.
 *  @author David Houchin
 *  @version 1.0 1/24/15
 */

#include "LevelEditor.h"

namespace SampleGame {
LevelEditor::LevelEditor(Game *game, int x, int y, int width, int height)
{
    this->game         = game;
    drawSquare         = true;
    hasDeletedEntity   = false;
    gridSize           = 32;
    title              = "Level Editor";
    sticky             = false;

    visible            = true;
    active             = true;
    isMoving           = false;
    id                 = -1;
    this->x            = x;
    this->y            = y;
    xMouseOffset       = 0;
    yMouseOffset       = 0;
    xOffset            = x - Engine::getInstance()->getViewportX();
    yOffset            = y - Engine::getInstance()->getViewportY();
    this->width        = width;
    this->height       = height;
    depth              = 0;

    ConfigReader* c    = game->getWindowManager()->getConfig();
    titleHeight        = c->getInt("window", "title_height", 16);

    textColor          = { static_cast<Uint8>(c->getInt("window", "text_r", 0)),
                           static_cast<Uint8>(c->getInt("window", "text_g", 0)),
                           static_cast<Uint8>(c->getInt("window", "text_b", 0)),
                           static_cast<Uint8>(c->getInt("window", "text_a", 255))};

    bodyColor          = { static_cast<Uint8>(c->getInt("window", "body_r", 192)),
                           static_cast<Uint8>(c->getInt("window", "body_g", 192)),
                           static_cast<Uint8>(c->getInt("window", "body_b", 192)),
                           static_cast<Uint8>(c->getInt("window", "body_a", 255))};

    titleActiveColor   = { static_cast<Uint8>(c->getInt("window", "title_r", 255)),
                           static_cast<Uint8>(c->getInt("window", "title_g", 0)),
                           static_cast<Uint8>(c->getInt("window", "title_b", 0)),
                           static_cast<Uint8>(c->getInt("window", "title_a", 255))};

    titleInactiveColor = { static_cast<Uint8>(c->getInt("window", "title_inactive_r", 120)),
                           static_cast<Uint8>(c->getInt("window", "title_inactive_g", 120)),
                           static_cast<Uint8>(c->getInt("window", "title_inactive_b", 120)),
                           static_cast<Uint8>(c->getInt("window", "title_inactive_a", 255))};

    spriteTopLeft      = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "topleft"));
    spriteTopRight     = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "topright"));
    spriteBottomLeft   = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "bottomleft"));
    spriteBottomRight  = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "bottomright"));
    spriteTopCenter    = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "topcenter"));
    spriteBottomCenter = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "bottomcenter"));
    spriteLeftCenter   = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "leftcenter"));
    spriteRightCenter  = ResourceManager::getInstance()->getSprite(
                         c->getString("window", "rightcenter"));

    font               = ResourceManager::getInstance()->getFont(
                         c->getString("window", "font"));

    objLabel = new Label(
                getX()+2,
                getY()+18,
                40,
                32);
    objLabel->setBorder(false);
    objLabel->setText("Object:");

    objTextBox = new TextBox(
                getX()+2,
                getY()+52,
                215,
                32);
    objTextBox->setBorder(true);

    objButton = new Button(
                getX()+225,
                getY()+52,
                40,
                32);
    objButton->setText("Set");
    objButton->setName("objbutton");

    lvlLabel = new Label(
                getX()+2,
                getY()+86,
                55,
                32);
    lvlLabel->setBorder(false);
    lvlLabel->setText("Level file:");

    lvlTextBox = new TextBox(
                getX()+2,
                getY()+120,
                215,
                32);
    lvlTextBox->setBorder(true);

    saveButton = new Button(
                getX()+225,
                getY()+110,
                40,
                25);
    saveButton->setText("Save");
    saveButton->setName("savebutton");

    loadButton = new Button(
                getX()+225,
                getY()+137,
                40,
                25);
    loadButton->setText("Load");
    loadButton->setName("loadbutton");

    clearLabel = new Label(
                getX()+2,
                getY()+170,
                95,
                32);
    clearLabel->setBorder(false);
    clearLabel->setText("Delete all objects:");
    clearLabel->setTextColor(255, 50, 50, 255);

    clearButton = new Button(
                getX()+100,
                getY()+170,
                80,
                32);
    clearButton->setText("Clear Level");
    clearButton->setName("clearbutton");

    addWidget(objLabel);
    addWidget(objTextBox);
    addWidget(objButton);
    addWidget(lvlLabel);
    addWidget(lvlTextBox);
    addWidget(saveButton);
    addWidget(loadButton);
    addWidget(clearLabel);
    addWidget(clearButton);
}

void LevelEditor::handleInput(Button *button)
{
    if (button->getName() == "objbutton") {
        selectedObject = translateString(objTextBox->getText());
    } else if (button->getName() == "savebutton") {
        if (lvlTextBox->getText() != "") {
            save(lvlTextBox->getText().c_str());
        }
    } else if (button->getName() == "loadbutton") {
        if (lvlTextBox->getText() != "") {
            game->loadLevel(lvlTextBox->getText());
        }
    } else if (button->getName() == "clearbutton") {
        game->getEngine()->destroyAllEntities();
        game->getEngine()->destroyAllTiles();
    }
}

void LevelEditor::draw()
{
    if (!visible) {
        return;
    }

    if (drawSquare) {
        drawRectangle(snapToGrid(game->getInput()->getMouseX(), gridSize),
                    snapToGrid(game->getInput()->getMouseY(), gridSize),
                    gridSize, gridSize, 50, 100, 150, 255);
    }

    //Draw body.
    drawFilledRectangle(x + 1, y + 1, width-2, height-2, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);

    //Draw borders, adjust position if clicked.
    spriteTopLeft->draw(x, y);
    spriteTopRight->draw(x + (width-3), y);
    spriteBottomLeft->draw(x, y + (height-3));
    spriteBottomRight->draw(x + (width-3), y + (height-3));

    spriteTopCenter->setWidth(width - 6);
    spriteTopCenter->draw(x + 3, y);
    spriteBottomCenter->setWidth(width - 6);
    spriteBottomCenter->draw(x + 3, y + (height-3));
    spriteLeftCenter->setHeight(height - 6);
    spriteLeftCenter->draw(x, y + 3);
    spriteRightCenter->setHeight(height - 6);
    spriteRightCenter->draw(x + (width-3), y + 3);

    //Draw title bar.
    if (active) {
        drawFilledRectangle(x + 1, y + 1, width-2, titleHeight, titleActiveColor.r, titleActiveColor.g, titleActiveColor.b, titleActiveColor.a);
    } else {
        drawFilledRectangle(x + 1, y + 1, width-2, titleHeight, titleInactiveColor.r, titleInactiveColor.g, titleInactiveColor.b, titleInactiveColor.a);
    }

    //Draw title text.
    if ((title != "") && (titleHeight != 0)) {
        font->setSDLColor(textColor);

        Engine::getInstance()->renderText(x + (width/2) - font->getTextWidth(title.c_str())/2,
                                          y + (titleHeight/2) - font->getTextHeight(title.c_str())/2,
                                          font, title.c_str());
    }

    //Draw child widgets
    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;
        widget->draw();
        iter++;
    }
}

void LevelEditor::update()
{
    //WINDOW STUFF
    if (!visible) {
        return;
    }

    int mx, my, tx, ty, vx, vy;
    mx = game->getInput()->getMouseX();
    my = game->getInput()->getMouseY();
    vx = game->getEngine()->getViewportX();
    vy = game->getEngine()->getViewportY();
    tx = x - vx;
    ty = y - vy;

    //If user clicked inside title:
    if ((!sticky) && (mx > tx) && (mx < (tx+width)) && (my > ty) && (my < (ty+titleHeight+2)) && game->getInput()->getMousePressed(MOUSE_LEFT)) {
        isMoving = true;
        xMouseOffset = mx - tx;
        yMouseOffset = my - ty;
    }
    else if ((game->getInput()->getMouseReleased(MOUSE_LEFT)) && (isMoving)) {
        isMoving = false;
        xOffset = tx;
        yOffset = ty;
    }

    if (isMoving) {
        x = mx - xMouseOffset + vx;
        y = my - yMouseOffset + vy;
    } else {
        setX(vx + xOffset);
        setY(vy + yOffset);
    }

    if (sticky) {
        setX(vx + xOffset);
        setY(vy + yOffset);
    }

    std::vector<Widget*>::iterator iter;
    Widget* widget;
    iter = children.begin();
    while (iter != children.end()) {
        widget = *iter;

        widget->setX(this->x + widget->getXOffset());
        widget->setY(this->y + widget->getYOffset());

        widget->update();
        iter++;
    }

    //EDITING STUFF
    if (((mx < tx) || (mx > (tx+width)) || (my < ty) || (my > (ty+height))) && game->getInput()->getMouseReleased(MOUSE_LEFT)) {
        if (selectedObject != eNone) {
            bool isEntity = true;
            //Figure out what objects are already in this spot and grab their pointers
            deleteEntity = game->getCollisionManager()->getPointMeetingEntity(mx, my);
            deleteTile = game->getCollisionManager()->getPointMeetingTile(mx, my, gridSize);

            //Place the new object depending on what user has selected
            switch (selectedObject) {
            case ePlayer: newEntity = new Player(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_ghost: newEntity = new Monster_ghost(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_wraith: newEntity = new Monster_wraith(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_specter: newEntity = new Monster_specter(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_zombie: newEntity = new Monster_zombie(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_skeleton: newEntity = new Monster_skeleton(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_skeletonCaptain: newEntity = new Monster_skeletonCaptain(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_skeletonMage: newEntity = new Monster_skeletonMage(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eMonster_vampire: newEntity = new Monster_vampire(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;

            case eFloor_brick: newTile = new Floor_brick(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_brickVines: newTile = new Floor_brickVines(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_brickMold: newTile = new Floor_brickMold(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_dirt: newTile = new Floor_dirt(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_grass: newTile = new Floor_grass(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_water: newTile = new Floor_water(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_water2: newTile = new Floor_water2(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_lava: newTile = new Floor_lava(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;
            case eFloor_lava2: newTile = new Floor_lava2(game);
                newTile->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize));
                isEntity = false; break;

            case eWall_brick: newEntity = new Wall_brick(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickVines: newEntity = new Wall_brickVines(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickMold: newEntity = new Wall_brickMold(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickStairsDown: newEntity = new Wall_brickStairsDown(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickStairsUp: newEntity = new Wall_brickStairsUp(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickDoorClosed: newEntity = new Wall_brickDoorClosed(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickDoorOpen: newEntity = new Wall_brickDoorOpen(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickGateClosed: newEntity = new Wall_brickGateClosed(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickGateOpen: newEntity = new Wall_brickGateOpen(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            case eWall_brickGrate: newEntity = new Wall_brickGrate(game);
                newEntity->setPosition(snapToGrid(mx, gridSize), snapToGrid(my, gridSize)); break;
            default: break;
            }

            //Now delete the old object
            if (isEntity) {
                if (deleteEntity != NULL) {
                    game->getEngine()->destroyEntity(deleteEntity->getID());
                }
            } else {
                if (deleteTile != NULL) {
                    game->getEngine()->destroyTile(deleteTile);
                }
            }
        }
    }

    //Right click to remove old objects, deleting entities before tiles
    if (((mx < tx) || (mx > (tx+width)) || (my < ty) || (my > (ty+height))) && game->getInput()->getMouseReleased(MOUSE_RIGHT)) {
        deleteEntity = game->getCollisionManager()->getPointMeetingEntity(mx, my);
        if (deleteEntity != NULL) {
            game->getEngine()->destroyEntity(deleteEntity->getID());
            hasDeletedEntity = true;
        }

        if (!hasDeletedEntity) {
            deleteTile = game->getCollisionManager()->getPointMeetingTile(mx, my, gridSize);
            if (deleteTile != NULL) {
                game->getEngine()->destroyTile(deleteTile);
            }
        }

        hasDeletedEntity = false;
    }
}

bool LevelEditor::save(const char* file)
{
    game->getLogger()->logMessage(0, "Saving level to '%s'", file);
    filename = file;
    remove(filename);
    saveFile.open(filename, std::ios::app);
    if (!saveFile.is_open()) {
        return false;
    }

    std::vector<Entity*> entities = game->getEngine()->getEntityList();

    std::vector<Entity*>::iterator iterE;
    Entity *entity;
    iterE = entities.begin();

    while (iterE != entities.end()) {
        entity = *iterE;
        saveFile << entity->getName() << " " << entity->getX() << " " << entity->getY() << "\n";
        iterE++;
    }

    std::vector<Tile*> tiles = game->getEngine()->getTileList();

    std::vector<Tile*>::iterator iterT;
    Tile *tile;
    iterT = tiles.begin();

    while (iterT != tiles.end()) {
        tile = *iterT;
        saveFile << tile->getName() << " " << tile->getX() << " " << tile->getY() << "\n";
        iterT++;
    }

    saveFile.close();

    return true;
}

LevelEditor::mapObject LevelEditor::translateString(std::string const& str)
{
    if (str == "width") return eWidth;
    else if (str == "height") return eHeight;
    else if (str == "player") return ePlayer;
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
}

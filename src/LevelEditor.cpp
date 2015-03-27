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
    drawGrid           = true;
    drawSquare         = true;
    hasDeletedEntity   = false;
    selectedObject     = eFloor_brick;
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

    gridColor          = { 200, 75, 75, 255 };
    squareColor        = { 50, 100, 150, 255 };

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

    objDropDownList = new DropDownList(
                getX()+2,
                getY()+52,
                215,
                32);
    objDropDownList->setBorder(true);
    objDropDownList->setName("objlist");
    addObjectsToDropDownList();
    objDropDownList->setPosition(0);

    lvlLabel = new Label(
                getX()+2,
                getY()+151,
                55,
                32);
    lvlLabel->setBorder(false);
    lvlLabel->setText("Level file:");

    lvlTextBox = new TextBox(
                getX()+2,
                getY()+185,
                215,
                32);
    lvlTextBox->setBorder(true);

    saveButton = new Button(
                getX()+225,
                getY()+175,
                40,
                25);
    saveButton->setText("Save");
    saveButton->setName("savebutton");

    loadButton = new Button(
                getX()+225,
                getY()+202,
                40,
                25);
    loadButton->setText("Load");
    loadButton->setName("loadbutton");

    resLabel = new Label(
                getX()+2,
                getY()+86,
                95,
                32);
    resLabel->setBorder(false);
    resLabel->setText("Level Dimensions:");

    widthTextBox = new TextBox(
                getX()+2,
                getY()+120,
                40,
                32);
    widthTextBox->setBorder(true);
    widthTextBox->setText(intToString(game->getLevelWidth()));

    heightTextBox = new TextBox(
                getX()+50,
                getY()+120,
                40,
                32);
    heightTextBox->setBorder(true);
    heightTextBox->setText(intToString(game->getLevelHeight()));

    resButton = new Button(
                getX()+225,
                getY()+120,
                40,
                25);
    resButton->setText("Set");
    resButton->setName("resbutton");

    clearLabel = new Label(
                getX()+2,
                getY()+250,
                95,
                32);
    clearLabel->setBorder(false);
    clearLabel->setText("Delete all objects:");
    clearLabel->setTextColor(255, 50, 50, 255);

    clearButton = new Button(
                getX()+100,
                getY()+250,
                80,
                32);
    clearButton->setText("Clear Level");
    clearButton->setName("clearbutton");

    closeButton = new Button(
                getX()+200,
                getY()+250,
                60,
                32);
    closeButton->setText("Close");
    closeButton->setName("closebutton");

    addWidget(objLabel);
    addWidget(lvlLabel);
    addWidget(lvlTextBox);
    addWidget(saveButton);
    addWidget(loadButton);
    addWidget(clearLabel);
    addWidget(clearButton);
    addWidget(closeButton);
    addWidget(resLabel);
    addWidget(widthTextBox);
    addWidget(heightTextBox);
    addWidget(resButton);
    addWidget(objDropDownList);
}

void LevelEditor::handleInput(Widget *widget)
{
    if (widget->getName() == "objlist") {
        selectedObject = translateString(objDropDownList->getPositionText());
    } else if (widget->getName() == "savebutton") {
        if (lvlTextBox->getText() != "") {
            save(lvlTextBox->getText().c_str());
        }
    } else if (widget->getName() == "loadbutton") {
        if (lvlTextBox->getText() != "") {
            game->loadLevel(lvlTextBox->getText());
        }
    } else if (widget->getName() == "clearbutton") {
        game->getEngine()->destroyAllEntities();
        game->getEngine()->destroyAllTiles();
    } else if (widget->getName() == "resbutton") {
        if ((widthTextBox->getText() != "") && (heightTextBox->getText() != "")) {
            game->setLevelWidth(stringToInt(widthTextBox->getText()));
            game->setLevelHeight(stringToInt(heightTextBox->getText()));
        }
    } else if (widget->getName() == "closebutton") {
        game->setEditorOpen(false);
    }
}

void LevelEditor::draw()
{
    if (!visible) {
        return;
    }

    //Draw the editing grid, if enabled.
    if (drawGrid) {
        int vLines, hLines, x1, y1, x2, y2;

        vLines = std::ceil(game->getEngine()->getViewportW()/gridSize);
        hLines = std::ceil(game->getEngine()->getViewportH()/gridSize);

        for (int i = 0; i < vLines; i++) {
            x1 = snapToGrid(i * gridSize + game->getEngine()->getViewportX(), gridSize);
            y1 = snapToGrid(game->getEngine()->getViewportY(), gridSize);
            x2 = x1;
            y2 = snapToGrid(i * gridSize + game->getEngine()->getViewportY() + game->getEngine()->getViewportH(), gridSize);

            drawLine(x1, y1, x2, y2, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
        }

        for (int i = 0; i < hLines; i++) {
            x1 = snapToGrid(game->getEngine()->getViewportX(), gridSize);
            y1 = snapToGrid(i * gridSize + game->getEngine()->getViewportY(), gridSize);
            x2 = snapToGrid(i * gridSize + game->getEngine()->getViewportX() + game->getEngine()->getViewportW(), gridSize);
            y2 = y1;

            drawLine(x1, y1, x2, y2, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
        }
    }

    //Draw a square at the cursor position aligned to the grid size, if enabled.
    if (drawSquare) {
        drawRectangle(snapToGrid(game->getInput()->getMouseX() + game->getEngine()->getViewportX(), gridSize),
                    snapToGrid(game->getInput()->getMouseY() + game->getEngine()->getViewportY(), gridSize),
                    gridSize, gridSize, squareColor.r, squareColor.g, squareColor.b, squareColor.a);
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

    int mx, my, tx, ty, vx, vy, vw, vh, ex, ey;
    mx = game->getInput()->getMouseX();
    my = game->getInput()->getMouseY();
    vx = game->getEngine()->getViewportX();
    vy = game->getEngine()->getViewportY();
    vw = game->getEngine()->getViewportW();
    vh = game->getEngine()->getViewportH();
    tx = x - vx;
    ty = y - vy;
    ex = mx + vx;
    ey = my + vy;

    Engine *engine = game->getEngine();

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
            bool isTile = false;
            bool isMonster = false;
            //Figure out what objects are already in this spot and grab their pointers
            deleteEntity = game->getCollisionManager()->getPointMeetingEntity(ex, ey);
            deleteTile = game->getCollisionManager()->getPointMeetingTile(ex, ey, gridSize);

            //Place the new object depending on what user has selected
            switch (selectedObject) {
            case ePlayer: newEntity = new Player(game); break;

            case eItem: newEntity = new ItemProp(game); break;

            case eMonster_ghost: newMonster = new Monster_ghost(game); isMonster = true; break;
            case eMonster_wraith: newMonster = new Monster_wraith(game); isMonster = true; break;
            case eMonster_specter: newMonster = new Monster_specter(game); isMonster = true; break;
            case eMonster_zombie: newMonster = new Monster_zombie(game); isMonster = true; break;
            case eMonster_skeleton: newMonster = new Monster_skeleton(game); isMonster = true; break;
            case eMonster_skeletonCaptain: newMonster = new Monster_skeletonCaptain(game); isMonster = true; break;
            case eMonster_skeletonMage: newMonster = new Monster_skeletonMage(game); isMonster = true; break;
            case eMonster_vampire: newMonster = new Monster_vampire(game); isMonster = true; break;

            case eFloor_brick: newTile = new Floor_brick(game); isTile = true; break;
            case eFloor_brickVines: newTile = new Floor_brickVines(game); isTile = true; break;
            case eFloor_brickMold: newTile = new Floor_brickMold(game); isTile = true; break;
            case eFloor_dirt: newTile = new Floor_dirt(game); isTile = true; break;
            case eFloor_grass: newTile = new Floor_grass(game); isTile = true; break;
            case eFloor_water: newTile = new Floor_water(game); isTile = true; break;
            case eFloor_water2: newTile = new Floor_water2(game); isTile = true; break;
            case eFloor_lava: newTile = new Floor_lava(game); isTile = true; break;
            case eFloor_lava2: newTile = new Floor_lava2(game); isTile = true; break;

            case eWall_brick: newEntity = new Wall_brick(game); break;
            case eWall_brickVines: newEntity = new Wall_brickVines(game); break;
            case eWall_brickMold: newEntity = new Wall_brickMold(game); break;
            case eWall_brickStairsDown: newEntity = new Wall_brickStairsDown(game); break;
            case eWall_brickStairsUp: newEntity = new Wall_brickStairsUp(game); break;
            case eWall_brickDoorClosed: newEntity = new Wall_brickDoorClosed(game); break;
            case eWall_brickDoorOpen: newEntity = new Wall_brickDoorOpen(game); break;
            case eWall_brickGateClosed: newEntity = new Wall_brickGateClosed(game); break;
            case eWall_brickGateOpen: newEntity = new Wall_brickGateOpen(game); break;
            case eWall_brickGrate: newEntity = new Wall_brickGrate(game); break;
            default: break;
            }

            //Now delete the old object
            if (isTile) {
                newTile->setPosition(snapToGrid(ex, gridSize), snapToGrid(ey, gridSize));

                if (deleteTile != NULL) {
                    engine->destroyTile(deleteTile);
                }
            } else if (isMonster) {
                newMonster->setPosition(snapToGrid(ex, gridSize), snapToGrid(ey, gridSize));
                game->addMonster(newMonster);

                if (deleteEntity != NULL) {
                    engine->destroyEntity(deleteEntity->getID());
                }
            } else {
                newEntity->setPosition(snapToGrid(ex, gridSize), snapToGrid(ey, gridSize));

                if (deleteEntity != NULL) {
                    engine->destroyEntity(deleteEntity->getID());
                }
            }
        }
    }

    //Right click to remove old objects, deleting entities before tiles
    if (((mx < tx) || (mx > (tx+width)) || (my < ty) || (my > (ty+height))) && game->getInput()->getMouseReleased(MOUSE_RIGHT)) {
        deleteEntity = game->getCollisionManager()->getPointMeetingEntity(ex, ey);
        if (deleteEntity != NULL) {
            engine->destroyEntity(deleteEntity->getID());
            hasDeletedEntity = true;
        }

        if (!hasDeletedEntity) {
            deleteTile = game->getCollisionManager()->getPointMeetingTile(ex, ey, gridSize);
            if (deleteTile != NULL) {
                engine->destroyTile(deleteTile);
            }
        }

        hasDeletedEntity = false;
    }

    //We can't use vx, vy, ex, or ey shorthand here as each test needs the immediate current viewport values that could have been
    //changed by the preceeding statement.

    //Height of status bar, used to make sure the viewport can see the bottom chunk of the map
    int statusHeight = 64;

    //Move viewport with cursor
    if ((mx + engine->getViewportX()) > engine->getViewportX() + vw - (gridSize)) {
        engine->setViewport(engine->getViewportX() + (gridSize/2), engine->getViewportY(), vw, vh);
    }
    if ((my + engine->getViewportY()) > engine->getViewportY() + vh - (gridSize)) {
        engine->setViewport(engine->getViewportX(), engine->getViewportY() + (gridSize/2), vw, vh);
    }
    if ((mx + engine->getViewportX()) < engine->getViewportX() + (gridSize)) {
        engine->setViewport(engine->getViewportX() - (gridSize/2), engine->getViewportY(), vw, vh);
    }
    if ((my + engine->getViewportY()) < engine->getViewportY() + (gridSize)) {
        engine->setViewport(engine->getViewportX(), engine->getViewportY() - (gridSize/2), vw, vh);
    }

    //Stop viewport at edges of screen
    if (engine->getViewportX() < 0) {
        engine->setViewport(0, engine->getViewportY(), vw, vh);
    }
    if (engine->getViewportY() < 0) {
        engine->setViewport(engine->getViewportX(), 0, vw, vh);
    }
    if (engine->getViewportX() > game->getLevelWidth() - vw) {
        engine->setViewport(game->getLevelWidth() - vw, engine->getViewportY(), vw, vh);
    }
    if (engine->getViewportY() > game->getLevelHeight() - vh + statusHeight) {
        engine->setViewport(engine->getViewportX(), game->getLevelHeight() - vh + statusHeight, vw, vh);
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

    saveFile << "width" << " " << game->getLevelWidth() << "\n";
    saveFile << "height" << " " << game->getLevelHeight() << "\n";

    std::vector<Entity*> entities = game->getEngine()->getEntityList();

    std::vector<Entity*>::iterator iterE;
    Entity *entity;
    iterE = entities.begin();

    while (iterE != entities.end()) {
        entity = *iterE;

        if (entity->getName() == "itemprop") {
            //If this is an item, we want to save the actual item alongside the item prop
            ItemProp *saveItem = (ItemProp *)entity;
            saveFile << saveItem->getName() << " " << saveItem->getX() << " " << saveItem->getY() << " " << saveItem->getItem()->getName() << "\n";
        } else if (entity->getName() == "wall_brickDoorClosed") {
            if (static_cast<Wall_brickDoorClosed*>(entity)->getLocked()) {
                saveFile << entity->getName() << " " << entity->getX() << " " << entity->getY() << " locked" << "\n";
            } else {
                saveFile << entity->getName() << " " << entity->getX() << " " << entity->getY() << "\n";
            }
        } else {
            saveFile << entity->getName() << " " << entity->getX() << " " << entity->getY() << "\n";
        }

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
    else if (str == "item") return eItem;
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

void LevelEditor::addObjectsToDropDownList()
{
    objDropDownList->addItem("floor_brick");
    objDropDownList->addItem("floor_brickVines");
    objDropDownList->addItem("floor_brickMold");
    objDropDownList->addItem("floor_dirt");
    objDropDownList->addItem("floor_grass");
    objDropDownList->addItem("floor_water");
    objDropDownList->addItem("floor_water2");
    objDropDownList->addItem("floor_lava");
    objDropDownList->addItem("floor_lava2");
    objDropDownList->addItem("wall_brick");
    objDropDownList->addItem("wall_brickVines");
    objDropDownList->addItem("wall_brickMold");
    objDropDownList->addItem("wall_brickStairsDown");
    objDropDownList->addItem("wall_brickStairsUp");
    objDropDownList->addItem("wall_brickDoorClosed");
    objDropDownList->addItem("wall_brickDoorOpen");
    objDropDownList->addItem("wall_brickGateClosed");
    objDropDownList->addItem("wall_brickGateOpen");
    objDropDownList->addItem("monster_ghost");
    objDropDownList->addItem("monster_wraith");
    objDropDownList->addItem("monster_zombie");
    objDropDownList->addItem("monster_skeleton");
    objDropDownList->addItem("monster_skeletonCaptain");
    objDropDownList->addItem("monster_skeletonMage");
    objDropDownList->addItem("monster_vampire");
    objDropDownList->addItem("player");
    objDropDownList->addItem("item");
}
}

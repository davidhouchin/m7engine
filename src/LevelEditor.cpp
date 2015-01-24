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
EditorWindow::EditorWindow(Game *game, int x, int y, int width, int height)
{
    this->game         = game;
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
    title              = "";

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
}

void EditorWindow::handleInput(std::string name)
{
    game->getLogger()->logMessage(1, "EditorWindow received input from %s", name.c_str());
}

LevelEditor::LevelEditor(Game *game)
{
    this->game = game;

    editorWindow = new EditorWindow(
                game,
                game->getEngine()->getViewportX()+64,
                game->getEngine()->getViewportY()+64,
                200,
                200);
    editorWindow->setTitle("Level Editor");
    editorWindow->setSticky(false);

    game->getWindowManager()->addWindow(editorWindow);

    Label *objLabel = new Label(
                editorWindow->getX()+2,
                editorWindow->getY()+18,
                40,
                32);
    objLabel->setBorder(false);
    objLabel->setText("Object:");

    TextBox *objTextBox = new TextBox(
                editorWindow->getX()+2,
                editorWindow->getY()+52,
                140,
                32);
    objTextBox->setBorder(true);

    Button *objButton = new Button(
                editorWindow->getX()+150,
                editorWindow->getY()+52,
                40,
                32);
    objButton->setText("Set");
    objButton->setName("setobject");

    Label *lvlLabel = new Label(
                editorWindow->getX()+2,
                editorWindow->getY()+86,
                55,
                32);
    lvlLabel->setBorder(false);
    lvlLabel->setText("Level file:");

    TextBox *lvlTextBox = new TextBox(
                editorWindow->getX()+2,
                editorWindow->getY()+120,
                140,
                32);
    lvlTextBox->setBorder(true);

    Button *lvlButton = new Button(
                editorWindow->getX()+150,
                editorWindow->getY()+120,
                40,
                32);
    lvlButton->setText("Save");
    lvlButton->setName("savelevel");

    editorWindow->addWidget(objLabel);
    editorWindow->addWidget(objTextBox);
    editorWindow->addWidget(objButton);
    editorWindow->addWidget(lvlLabel);
    editorWindow->addWidget(lvlTextBox);
    editorWindow->addWidget(lvlButton);
}
}

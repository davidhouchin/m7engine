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
    title              = "Level Editor";

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
                140,
                32);
    objTextBox->setBorder(true);

    objButton = new Button(
                getX()+150,
                getY()+52,
                40,
                32);
    objButton->setText("Set");
    objButton->setName("setobject");

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
                140,
                32);
    lvlTextBox->setBorder(true);

    lvlButton = new Button(
                getX()+150,
                getY()+120,
                40,
                32);
    lvlButton->setText("Save");
    lvlButton->setName("savelevel");

    addWidget(objLabel);
    addWidget(objTextBox);
    addWidget(objButton);
    addWidget(lvlLabel);
    addWidget(lvlTextBox);
    addWidget(lvlButton);
}

void LevelEditor::handleInput(Button *button)
{
    game->getLogger()->logMessage(1, "EditorWindow received %s from %s", button->getText().c_str(), button->getName().c_str());
}

void LevelEditor::draw()
{
    if (!visible) {
        return;
    }

    if (drawSquare) {
        drawRectangle(snapToGrid(game->getInput()->getMouseX(), 32),
                    snapToGrid(game->getInput()->getMouseY(), 32),
                    32, 32, 50, 100, 150, 255);
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
}

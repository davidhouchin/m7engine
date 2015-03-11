/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  CommonDialogs
 *  CommonDialogs.cpp
 *  Purpose: Commonly used dialog classes.
 *  @author David Houchin
 *  @version 1.0 3/8/15
 */

#include "CommonDialogs.h"

namespace SampleGame {
MessageBox::MessageBox(Game *game, std::string titleText, std::string messageText)
{
    title              = titleText;
    sticky             = false;

    visible            = true;
    active             = true;
    isMoving           = false;
    id                 = -1;
    x                  = 0;
    y                  = 0;
    xMouseOffset       = 0;
    yMouseOffset       = 0;
    xOffset            = x - Engine::getInstance()->getViewportX();
    yOffset            = y - Engine::getInstance()->getViewportY();
    width              = 200;
    height             = 110;
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

    msgLabel = new Label(
                x+2,
                y+18,
                40,
                32);
    msgLabel->setBorder(false);
    msgLabel->setText(messageText);

    okButton = new Button(
                x+100,
                y+70,
                80,
                32);
    okButton->setText("Ok");
    okButton->setName("okbutton");

    //Set window size to be a little larger than the string size
    width = msgLabel->getFont()->getTextWidth(msgLabel->getText().c_str()) + 50;

    //Expand label width to size of window and center button
    msgLabel->setWidth(width - 4);
    okButton->setX(x + (width/2) - (okButton->getWidth()/2));

    addWidget(msgLabel);
    addWidget(okButton);

    x = Engine::getInstance()->getViewportW() - (width/2);
    y = Engine::getInstance()->getViewportH() - (height/2);
    xOffset = x - Engine::getInstance()->getViewportW()/2;
    yOffset = y - Engine::getInstance()->getViewportH()/2;
}

void MessageBox::handleInput(Widget *widget)
{
    if (widget->getName() == "okbutton") {
        //TODO: SEGFAULT if calling from Game::GetWindowManager()?
        WindowManager::getInstance()->destroyWindow(id);
    }
}
}

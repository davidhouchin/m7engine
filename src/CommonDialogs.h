/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  CommonDialogs
 *  CommonDialogs.h
 *  Purpose: Commonly used dialog classes.
 *  @author David Houchin
 *  @version 1.0 3/8/15
 */

#ifndef COMMONDIALOGS_H
#define COMMONDIALOGS_H

#include "Game.h"

namespace SampleGame {
class MessageBox : public Window {
private:
    Game *game;
    Label *msgLabel;
    Button *okButton;

    void setString(std::string text) { msgLabel->setText(text); }

public:
    MessageBox(Game *game, std::string titleText, std::string messageText);
    void handleInput(Widget *widget);
};
}

#endif

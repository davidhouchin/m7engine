/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Interface
 *  Interface.h
 *  Purpose: GUI for player interface
 *  @author David Houchin
 *  @version 1.0 3/25/15
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Game.h"
#include "Player.h"

class Player;

namespace SampleGame {
class InventoryWindow : public Window {
private:
    Game *game;
    Player *player;

    Label *headLabel, *torsoLabel, *handLabel, *footLabel, *weaponLabel,
            *headImageLabel, *torsoImageLabel, *handImageLabel, *footImageLabel, *weaponImageLabel,
            *nameLabel, *weightLabel, *attackLabel, *defenseLabel, *itemLabel, *itemImageLabel, *itemDescriptionLabel,
            *borderLabel;
    DropDownList *itemList;
    Button *equipButton, *dropButton, *closeButton;

    Item *selectedItem;

    void populateItemList();

public:
    InventoryWindow(Game *game, Player *player);
    void handleInput(Widget *widget);
    void update();
};

class StatusBar : public Window {
private:
    Game *game;
    Player *player;

    Label *nameLabel, *hpLabel, *mpLabel, *messageBox, *message1Label, *message2Label, *message3Label;
    Button *inventoryButton, *editorButton, *quitButton;

    InventoryWindow *inventory;

public:
    StatusBar(Game *game, Player *player);
    ~StatusBar();

    void message(std::string text, ...);

    void handleInput(Widget *widget);
};
}

#endif

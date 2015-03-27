/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Interface
 *  Interface.cpp
 *  Purpose: GUI for player interface.
 *  @author David Houchin
 *  @version 1.0 3/25/15
 */

#include "Interface.h"
#include "Player.h"

namespace SampleGame {
StatusBar::StatusBar(Game *game, Player *player)
{
    this->game = game;
    this->player = player;

    title              = "";
    sticky             = true;

    visible            = true;
    active             = true;
    isMoving           = false;
    id                 = -1;
    x                  = 0;//game->getEngine()->getViewportW();
    y                  = game->getEngine()->getViewportH() - 64;
    xMouseOffset       = 0;
    yMouseOffset       = 0;
    xOffset            = x - Engine::getInstance()->getViewportX();
    yOffset            = y - Engine::getInstance()->getViewportY();
    width              = game->getEngine()->getViewportW();
    height             = 64;
    depth              = 0;

    ConfigReader* c    = game->getWindowManager()->getConfig();
    titleHeight        = 0;

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

    nameLabel = new Label(
                x+2,
                y+2,
                100,
                24);
    nameLabel->setBorder(true);
    nameLabel->setText("Name: " + player->name);

    hpLabel = new Label(
                x+110,
                y+2,
                70,
                24);
    hpLabel->setBorder(true);
    hpLabel->setText("HP: " + intToString(player->hp) + "/" + intToString(player->hpMax));
    hpLabel->setTextColor(255, 80, 80, 255);

    mpLabel = new Label(
                x+190,
                y+2,
                70,
                24);
    mpLabel->setBorder(true);
    mpLabel->setText("MP: " + intToString(player->mp) + "/" + intToString(player->mpMax));
    mpLabel->setTextColor(80, 80, 255, 255);

    messageBox = new Label(
                x+280,
                y+2,
                350,
                60);
    messageBox->setBorder(true);
    messageBox->setBody(true);
    messageBox->setBodyColor(0, 0, 0, 255);

    message1Label = new Label(
                x+284,
                y+42,
                340,
                20);
    message1Label->setBorder(false);
    message1Label->setTextColor(255, 255, 255, 255);
    message1Label->setText("");

    message2Label = new Label(
                x+284,
                y+24,
                340,
                20);
    message2Label->setBorder(false);
    message2Label->setTextColor(255, 255, 255, 255);
    message2Label->setText("");

    message3Label = new Label(
                x+284,
                y+6,
                340,
                20);
    message3Label->setBorder(false);
    message3Label->setTextColor(255, 255, 255, 255);
    message3Label->setText("");

    inventoryButton = new Button(
                x+2,
                y+30,
                80,
                32);
    inventoryButton->setText("Inventory");
    inventoryButton->setName("inventorybutton");

    editorButton = new Button(
                x+92,
                y+30,
                80,
                32);
    editorButton->setText("Editor");
    editorButton->setName("editorbutton");

    quitButton = new Button(
                x+180,
                y+30,
                80,
                32);
    quitButton->setText("Quit");
    quitButton->setName("quitbutton");

    addWidget(nameLabel);
    addWidget(hpLabel);
    addWidget(mpLabel);
    addWidget(messageBox);
    addWidget(message1Label);
    addWidget(message2Label);
    addWidget(message3Label);
    addWidget(inventoryButton);
    addWidget(editorButton);
    addWidget(quitButton);

    inventory = new InventoryWindow(game, player);
    inventory->setVisible(false);
    game->getWindowManager()->addWindow(inventory);
}

StatusBar::~StatusBar()
{
    game->getWindowManager()->destroyWindow(inventory->getID());
}

void StatusBar::handleInput(Widget *widget)
{
    if (widget->getName() == "inventorybutton") {
        inventory->setVisible(true);
    } else if (widget->getName() == "editorbutton") {
        game->setEditorOpen(true);
    } else if (widget->getName() == "quitbutton") {
        game->quit();
    }
}

void StatusBar::message(std::string text, ...)
{
    char buffer[999];
    va_list args;
    va_start(args, text);
    vsprintf(buffer, text.c_str(), args);
    va_end(args);

    std::string result(buffer);

    game->getLogger()->logMessage(0, result);

    message3Label->setText(message2Label->getText());
    message2Label->setText(message1Label->getText());
    message1Label->setText(result);
}

InventoryWindow::InventoryWindow(Game *game, Player *player)
{
    this->game         = game;
    this->player       = player;
    selectedItem       = NULL;

    title              = "Inventory";
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
    width              = 300;
    height             = 300;
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

    ResourceManager* r = ResourceManager::getInstance();

    spriteTopLeft      = r->getSprite(c->getString("window", "topleft"));
    spriteTopRight     = r->getSprite(c->getString("window", "topright"));
    spriteBottomLeft   = r->getSprite(c->getString("window", "bottomleft"));
    spriteBottomRight  = r->getSprite( c->getString("window", "bottomright"));
    spriteTopCenter    = r->getSprite(c->getString("window", "topcenter"));
    spriteBottomCenter = r->getSprite( c->getString("window", "bottomcenter"));
    spriteLeftCenter   = r->getSprite(c->getString("window", "leftcenter"));
    spriteRightCenter  = r->getSprite(c->getString("window", "rightcenter"));

    font               = r->getFont(c->getString("window", "font"));

    headLabel = new Label(
                x+34,
                y+18,
                80,
                32);
    headLabel->setBorder(false);
    headLabel->setCenterText(false);
    if (player->headArmor != NULL)
        headLabel->setText("Head: " + player->headArmor->getName());
    else
        headLabel->setText("Head: None");

    torsoLabel = new Label(
                x+34,
                y+48,
                80,
                32);
    torsoLabel->setBorder(false);
    torsoLabel->setCenterText(false);
    if (player->torsoArmor != NULL)
        torsoLabel->setText("Torso: " + player->torsoArmor->getName());
    else
        torsoLabel->setText("Torso: None");

    handLabel = new Label(
                x+34,
                y+80,
                80,
                32);
    handLabel->setBorder(false);
    handLabel->setCenterText(false);
    if (player->handArmor != NULL)
        handLabel->setText("Hand: " + player->handArmor->getName());
    else
        handLabel->setText("Hand: None");

    footLabel = new Label(
                x+34,
                y+112,
                80,
                32);
    footLabel->setBorder(false);
    footLabel->setCenterText(false);
    if (player->footArmor != NULL)
        footLabel->setText("Foot: " + player->footArmor->getName());
    else
        footLabel->setText("Foot: None");

    weaponLabel = new Label(
                x+34,
                y+144,
                80,
                32);
    weaponLabel->setBorder(false);
    weaponLabel->setCenterText(false);
    if (player->weapon != NULL)
        weaponLabel->setText("Weapon: " + player->weapon->getName());
    else
        weaponLabel->setText("Weapon: None");

    headImageLabel = new Label(
                x+2,
                y+18,
                32,
                32);
    headImageLabel->setBorder(true);
    headImageLabel->setUseImage(true);
    if (player->headArmor != NULL)
        headImageLabel->setImage(r->getSprite(player->headArmor->getImageName()));
    else
        headImageLabel->setImage(NULL);

    torsoImageLabel = new Label(
                x+2,
                y+48,
                32,
                32);
    torsoImageLabel->setBorder(true);
    torsoImageLabel->setUseImage(true);
    if (player->torsoArmor != NULL)
        torsoImageLabel->setImage(r->getSprite(player->torsoArmor->getImageName()));
    else
        torsoImageLabel->setImage(NULL);

    handImageLabel = new Label(
                x+2,
                y+80,
                32,
                32);
    handImageLabel->setBorder(true);
    handImageLabel->setUseImage(true);
    if (player->handArmor != NULL)
        handImageLabel->setImage(r->getSprite(player->handArmor->getImageName()));
    else
        handImageLabel->setImage(NULL);

    footImageLabel = new Label(
                x+2,
                y+112,
                32,
                32);
    footImageLabel->setBorder(true);
    footImageLabel->setUseImage(true);
    if (player->footArmor != NULL)
        footImageLabel->setImage(r->getSprite(player->footArmor->getImageName()));
    else
        footImageLabel->setImage(NULL);

    weaponImageLabel = new Label(
                x+2,
                y+144,
                32,
                32);
    weaponImageLabel->setBorder(true);
    weaponImageLabel->setUseImage(true);
    if (player->weapon != NULL)
        weaponImageLabel->setImage(r->getSprite(player->weapon->getImageName()));
    else
        weaponImageLabel->setImage(NULL);

    nameLabel = new Label(
                x+180,
                y+18,
                110,
                24);
    nameLabel->setBorder(true);
    nameLabel->setText("Name: " + player->name);

    weightLabel = new Label(
                x+180,
                y+46,
                110,
                24);
    weightLabel->setBorder(true);
    weightLabel->setText("Weight: " + intToString(player->weight) + " / " + intToString(player->weightCapacity));

    attackLabel = new Label(
                x+180,
                y+74,
                110,
                24);
    attackLabel->setBorder(true);
    attackLabel->setText("");

    defenseLabel = new Label(
                x+180,
                y+102,
                110,
                24);
    defenseLabel->setBorder(true);
    defenseLabel->setText("Defense: " + intToString(player->defense));

    itemList = new DropDownList(
                x+180,
                y+140,
                110,
                24);
    itemList->setBorder(true);
    itemList->setName("itemlist");
    populateItemList();

    borderLabel = new Label(
                x+2,
                y+190,
                296,
                70);
    borderLabel->setBorder(true);

    itemLabel = new Label(
                x+38,
                y+192,
                80,
                24);
    itemLabel->setBorder(false);
    itemLabel->setCenterText(false);

    itemDescriptionLabel = new Label(
                x+4,
                y+220,
                200,
                40);
    itemDescriptionLabel->setBorder(false);
    itemDescriptionLabel->setCenterText(false);

    itemImageLabel = new Label(
                x+2,
                y+192,
                32,
                32);
    itemImageLabel->setUseImage(true);

    equipButton = new Button(
                x+2,
                y+264,
                80,
                32);
    equipButton->setText("Use");
    equipButton->setName("equipbutton");

    dropButton = new Button(
                x+90,
                y+264,
                80,
                32);
    dropButton->setText("Drop");
    dropButton->setName("dropbutton");

    closeButton = new Button(
                x+214,
                y+264,
                80,
                32);
    closeButton->setText("Close");
    closeButton->setName("closebutton");

    addWidget(headLabel);
    addWidget(torsoLabel);
    addWidget(handLabel);
    addWidget(footLabel);
    addWidget(weaponLabel);
    addWidget(headImageLabel);
    addWidget(torsoImageLabel);
    addWidget(handImageLabel);
    addWidget(footImageLabel);
    addWidget(weaponImageLabel);
    addWidget(nameLabel);
    addWidget(weightLabel);
    addWidget(attackLabel);
    addWidget(defenseLabel);
    addWidget(borderLabel);
    addWidget(itemLabel);
    addWidget(itemDescriptionLabel);
    addWidget(itemImageLabel);
    addWidget(equipButton);
    addWidget(dropButton);
    addWidget(closeButton);
    addWidget(itemList);

    x = Engine::getInstance()->getViewportW() - (width/2);
    y = Engine::getInstance()->getViewportH() - (height/2);
    xOffset = x - Engine::getInstance()->getViewportW()/2;
    yOffset = y - Engine::getInstance()->getViewportH()/2;
}

void InventoryWindow::handleInput(Widget *widget)
{
    if (widget->getName() == "closebutton") {
        setVisible(false);
    } else if (widget->getName() == "itemlist") {
        std::vector<std::string> selectItem = split(itemList->getPositionText(), ' ');
        selectedItem = player->getInventoryItem(selectItem[0]);
    } else if (widget->getName() == "equipbutton") {
        if (selectedItem == NULL)
            return;
        if ((selectedItem->getItemClass() == Item::armor) || (selectedItem->getItemClass() == Item::weapon)) {
            if (selectedItem->getEquipped()) {
                player->unequipItem(selectedItem->getName());
            } else {
                player->equipItem(selectedItem->getName());
            }
        } else {
            player->useItem(selectedItem->getName());
        }
    } else if (widget->getName() == "dropbutton") {
        if (selectedItem == NULL)
            return;
        if ((selectedItem->getEquipped()) && (selectedItem->getCount() == 1)) {
            player->unequipItem(selectedItem->getName());
        }
        player->dropItem(selectedItem->getName());
        selectedItem = NULL;
        itemList->setText("");
    }
}

void InventoryWindow::update()
{
    if (game->getInput()->getKeyReleased(KEY_I)) {
        if (visible) {
            visible = false;
        } else {
            visible = true;
        }
    }

    if (!visible) {
        return;
    }

    int mx, my, tx, ty, vx, vy;
    mx = InputManager::getInstance()->getMouseX();
    my = InputManager::getInstance()->getMouseY();
    vx = Engine::getInstance()->getViewportX();
    vy = Engine::getInstance()->getViewportY();
    tx = x - vx;
    ty = y - vy;

    //If user clicked inside title:
    if ((!sticky) && (mx > tx) && (mx < (tx+width)) && (my > ty) && (my < (ty+titleHeight+2)) && InputManager::getInstance()->getMousePressed(MOUSE_LEFT)) {
        isMoving = true;
        xMouseOffset = mx - tx;
        yMouseOffset = my - ty;
    }
    else if ((InputManager::getInstance()->getMouseReleased(MOUSE_LEFT)) && (isMoving)) {
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

    //Update all the images and text shown in the inventory window
    if (player->headArmor != NULL)
        headLabel->setText("Head: " + player->headArmor->getLongName());
    else
        headLabel->setText("Head: None");

    if (player->torsoArmor != NULL)
        torsoLabel->setText("Torso: " + player->torsoArmor->getLongName());
    else
        torsoLabel->setText("Torso: None");

    if (player->handArmor != NULL)
        handLabel->setText("Hand: " + player->handArmor->getLongName());
    else
        handLabel->setText("Hand: None");

    if (player->footArmor != NULL)
        footLabel->setText("Foot: " + player->footArmor->getLongName());
    else
        footLabel->setText("Foot: None");

    if (player->weapon != NULL)
        weaponLabel->setText("Weapon: " + player->weapon->getLongName());
    else
        weaponLabel->setText("Weapon: None");

    if (player->headArmor != NULL)
        headImageLabel->setImage(ResourceManager::getInstance()->getSprite(player->headArmor->getImageName()));
    else
        headImageLabel->setImage(NULL);

    if (player->torsoArmor != NULL)
        torsoImageLabel->setImage(ResourceManager::getInstance()->getSprite(player->torsoArmor->getImageName()));
    else
        torsoImageLabel->setImage(NULL);

    if (player->handArmor != NULL)
        handImageLabel->setImage(ResourceManager::getInstance()->getSprite(player->handArmor->getImageName()));
    else
        handImageLabel->setImage(NULL);

    if (player->footArmor != NULL)
        footImageLabel->setImage(ResourceManager::getInstance()->getSprite(player->footArmor->getImageName()));
    else
        footImageLabel->setImage(NULL);

    if (player->weapon != NULL) {
        weaponImageLabel->setImage(ResourceManager::getInstance()->getSprite(player->weapon->getImageName()));
        attackLabel->setText("Attack: " + intToString(player->damage + player->weapon->getMinDamage()) + "-" + intToString(player->weapon->getMaxDamage()));
    } else {
        weaponImageLabel->setImage(NULL);
        attackLabel->setText("Attack: " + intToString(player->damage));
    }

    nameLabel->setText("Name: " + player->name);
    weightLabel->setText("Weight: " + intToString(player->weight) + " / " + intToString(player->weightCapacity));
    defenseLabel->setText("Defense: " + intToString(player->defense));

    if (selectedItem != NULL) {
        itemLabel->setText(selectedItem->getLongName());
        itemDescriptionLabel->setText(selectedItem->getDescription());
        itemImageLabel->setImage(ResourceManager::getInstance()->getSprite(selectedItem->getImageName()));
    } else {
        itemLabel->setText("No Item Selected");
        itemDescriptionLabel->setText("");
        itemImageLabel->setImage(NULL);
    }

    if ((selectedItem != NULL) && (player->getInventoryItem(selectedItem->getName()) == NULL))
        selectedItem = NULL;

    populateItemList();
}

void InventoryWindow::populateItemList()
{
    itemList->clearItems();

    std::vector<Item*> inventory = player->inventory;
    std::vector<Item*>::iterator iter;
    Item *item;

    iter = inventory.begin();

    while (iter != inventory.end()) {
        item = *iter;
        itemList->addItem(item->getName() + " x" + intToString(item->getCount()));
        iter++;
    }
}
}

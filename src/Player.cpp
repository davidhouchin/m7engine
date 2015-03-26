/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Player
 *  Player.cpp
 *  Purpose: Player character class.
 *  @author David Houchin
 *  @version 1.0 1/21/15
 */

#include "Player.h"
#include "Game.h"
#include "Interface.h"
#include "Props.h"

namespace SampleGame {
Player::Player(Game *game)
{
    this->game = game;

    setName("player");
    setProperties(game->getObjectConfig(), getName());
    
    name = "The Dude";

    level = 1; //Player level
    exp = 0; //Total experience

    hp = 30; //Health
    mp = 10; //Magic points

    strength = 10; //Dictates melee attacks and carry capacity
    intellect = 10; //Dictates magic damage
    dexterity = 10; //Dictates ranged attacks and defense

    damage = 5; //Physical base damage per attack
    defense = 10; //Physical base armor
    weight = 0; //Current weight being carried
    weightCapacity = 100; //Total weight that can be carried

    speed = 32; //Interval which player snaps to

    runSpeed = 5; //Time between moving while running (holding down an arrow key)
    runDelay = 20; //Time before triggering running
    runCounter = 0; //Utility variable to keep track of runSpeed
    runDelayCounter = 0; //Utility variable to keep track of runDelay
    running = false; //Is player running?

    moves = 0;
    dead = false;
    notStarted = true;
    moved = false;

    footArmor = NULL;
    torsoArmor = NULL;
    handArmor = NULL;
    headArmor = NULL;
    weapon = NULL;

    statusBar = new StatusBar(game, this);

    Item_sword *sword = new Item_sword();
    addItem(sword);
    equipItem("sword");

    game->getWindowManager()->addWindow(statusBar);

    statusBar->message("You step from the stairs into a dank corridor.");
}

Player::~Player()
{
    game->getWindowManager()->destroyWindow(statusBar->getID());
}

void Player::update()
{
    InputManager *input = game->getInput();
    CollisionManager *collision = game->getCollisionManager();
    ResourceManager *resources = game->getResourceManager();
    Engine *engine = game->getEngine();

    Entity *collide;

    //Do some startup work
    if (notStarted) {
        startx = getX();
        starty = getY();
        notStarted = false;
    }

    if (input->getKeyReleased(KEY_F1)) {
        displayInventory();
    }

    //Key movement code
    if (!dead) {
        if (input->getKeyPressed(KEY_UP)) {
            collide = collision->getPointMeetingEntity(getXBBox(), getYBBox() - speed);
            if (collide == NULL) {
                setY(getY() - 32);
                moved = true;
            } else if (collide->getFamily() == "monster") {
                attack(dynamic_cast<Monster*>(collide));
                moved = true;
            } else if (collide->getFamily() != "wall") {
                setY(getY() - 32);
                moved = true;
            }
        } else if (input->getKeyPressed(KEY_DOWN)) {
            collide = collision->getPointMeetingEntity(getXBBox(), getYBBox() + speed);
            if (collide == NULL) {
                setY(getY() + 32);
                moved = true;
            } else if (collide->getFamily() == "monster") {
                attack(dynamic_cast<Monster*>(collide));
                moved = true;
            } else if (collide->getFamily() != "wall") {
                setY(getY() + 32);
                moved = true;
            }
        } else if (input->getKeyPressed(KEY_LEFT)) {
            collide = collision->getPointMeetingEntity(getXBBox() - speed, getYBBox());
            if (collide == NULL) {
                setX(getX() - 32);
                moved = true;
            } else if (collide->getFamily() == "monster") {
                attack(dynamic_cast<Monster*>(collide));
                moved = true;
            } else if (collide->getFamily() != "wall") {
                setX(getX() - 32);
                moved = true;
            }
        } else if (input->getKeyPressed(KEY_RIGHT)) {
            collide = collision->getPointMeetingEntity(getXBBox() + speed, getYBBox());
            if (collide == NULL) {
                setX(getX() + 32);
                moved = true;
            } else if (collide->getFamily() == "monster") {
                attack(dynamic_cast<Monster*>(collide));
                moved = true;
            } else if (collide->getFamily() != "wall") {
                setX(getX() + 32);
                moved = true;
            }
        }

        if ((input->getKeyReleased(KEY_UP)) ||
                (input->getKeyReleased(KEY_DOWN)) ||
                (input->getKeyReleased(KEY_LEFT)) ||
                (input->getKeyReleased(KEY_RIGHT))) {
            running = false;
        }

        if (input->getKeyHeld(KEY_UP)) {
            collide = collision->getPointMeetingEntity(getXBBox(), getYBBox() - speed);
            if (!running) {
                if (runDelayCounter < runDelay) {
                    runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if ((collide == NULL) || ((collide != NULL) && ((collide->getFamily() != "wall") && (collide->getFamily() != "monster")))) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setY(getY() - 32);
                    runCounter = 0;
                    moved = true;
                }
            }
        } else if (input->getKeyHeld(KEY_DOWN)) {
            collide = collision->getPointMeetingEntity(getXBBox(), getYBBox() + speed);
            if (!running) {
                if (runDelayCounter < runDelay) {
                     runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if ((collide == NULL) || ((collide != NULL) && ((collide->getFamily() != "wall") && (collide->getFamily() != "monster")))) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setY(getY() + 32);
                    runCounter = 0;
                    moved = true;
                }
            }
        } else if (input->getKeyHeld(KEY_LEFT)) {
            collide = collision->getPointMeetingEntity(getXBBox() - speed, getYBBox());
            if (!running) {
                if (runDelayCounter < runDelay) {
                    runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if ((collide == NULL) || ((collide != NULL) && ((collide->getFamily() != "wall") && (collide->getFamily() != "monster")))) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setX(getX() - 32);
                    runCounter = 0;
                    moved = true;
                }
            }
        } else if (input->getKeyHeld(KEY_RIGHT)) {
            collide = collision->getPointMeetingEntity(getXBBox() + speed, getYBBox());
            if (!running) {
                if (runDelayCounter < runDelay) {
                    runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if ((collide == NULL) || ((collide != NULL) && ((collide->getFamily() != "wall") && (collide->getFamily() != "monster")))) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setX(getX() + 32);
                    runCounter = 0;
                    moved = true;
                }
            }
        }
    }

    //Move viewport along with character
    if (!game->getEditorOpen()) {
        int statusHeight = 64;

        engine->setViewport((getX() + getXOffset()) - (engine->getScreenWidth()/2),
                            (getY() + getYOffset()) - (engine->getScreenHeight()/2),
                            engine->getScreenWidth(),
                            engine->getScreenHeight());

        //Stop viewport at edges of screen
        //Stop at left side of screen
        if (engine->getViewportX() < 0) {
            engine->setViewport(0, engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
        }
        //Stop at top of screen
        if (engine->getViewportY() < 0) {
            engine->setViewport(engine->getViewportX(), 0, engine->getViewportW(), engine->getViewportH());
        }
        //Stop at rightmost side of level
        if (engine->getViewportX() > game->getLevelWidth() - engine->getViewportW()) {
            engine->setViewport(engine->getScreenWidth() - engine->getViewportW(), engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
        }
        //Stop at bottom of level
        if (engine->getViewportY() > game->getLevelHeight() - engine->getViewportH() + statusHeight) {
            engine->setViewport(engine->getViewportX(), engine->getScreenHeight() - engine->getViewportH() + statusHeight, engine->getViewportW(), engine->getViewportH());
        }
    }

    if (moved) {
        game->turn();
        moved = false;
    }
}

void Player::collision(Entity *other)
{
    //Some bug is causing player to trigger collision with everything on very first frame, need to figure out what causes this...
    if (notStarted) {
        return;
    }

    if (other->getFamily() == "monster") {
        if (!dead) {
            dead = true;
            game->getEngine()->playSound(game->getResourceManager()->getSound("boom"), 0);
            timer[0] = 60;
            setAlpha(120);
        }
    } else if (other->getFamily() == "item") {
        if (!dead) {
            if (game->getInput()->getKeyReleased(KEY_SPACE)) {
                ItemProp *pickup = (ItemProp *)other;
                if (addItem(pickup->getItem())) {
                    //If this item is better than what we currently have, equip it
                    if (pickup->getItem()->getItemClass() == Item::armor) {
                        switch (pickup->getItem()->getArmorClass()) {
                        case Item::head:
                            if ((headArmor == NULL) || (pickup->getItem()->getArmor() > headArmor->getArmor()))
                                equipItem(pickup->getItem()->getName());
                            break;
                        case Item::torso:
                            if ((torsoArmor == NULL) || (pickup->getItem()->getArmor() > torsoArmor->getArmor()))
                                equipItem(pickup->getItem()->getName());
                            break;
                        case Item::hand:
                            if ((handArmor == NULL) || (pickup->getItem()->getArmor() > handArmor->getArmor()))
                                equipItem(pickup->getItem()->getName());
                            break;
                        case Item::foot:
                            if ((footArmor == NULL) || (pickup->getItem()->getArmor() > footArmor->getArmor()))
                                equipItem(pickup->getItem()->getName());
                            break;
                        }
                    } else if (pickup->getItem()->getItemClass() == Item::weapon) {
                        if ((weapon == NULL) || (pickup->getItem()->getMinDamage() > weapon->getMinDamage()))
                            equipItem(pickup->getItem()->getName());
                    }

                    //Destroy the item prop
                    game->getEngine()->destroyEntity(pickup->getID());
                }
            }
        }
    }
}

void Player::alarm(int timerNum)
{
    if (timerNum == 0) {
        setOriginToImageCenter();
        setX(startx);
        setY(starty);
        dead = false;
        setAlpha(255);
    }
}

void Player::attack(Monster *target)
{
    int def = target->getDefense();

    int wepDmg;
    if (weapon != NULL) {
        wepDmg = randomRangeInt(weapon->getMinDamage(), weapon->getMaxDamage());
    } else {
        wepDmg = 0;
    }
    int dmg = (damage + wepDmg) - def;

    if (dmg < 0) {
        dmg = 0;
    }

    target->setHp(target->getHp() - dmg);

    statusBar->message("You hit the %s for %i damage.", target->getName().c_str(), dmg);

    if (target->getHp() <= 0) {
        int expGain = target->getExp();
        exp += expGain;
        target->die();
        statusBar->message("You gained %i experience.", expGain);
    }

    target->setAlpha(120);
    target->setTimer(0, 30);
}

Item* Player::getInventoryItem(std::string name)
{
    std::vector<Item*>::iterator iterI;
    Item *item;
    iterI = inventory.begin();

    while (iterI != inventory.end()) {
        item = *iterI;
        if (item->getName() == name) {
            return item;
        } else {
            iterI++;
        }
    }

    return NULL;
}

bool Player::addItem(Item *item)
{
    if ((weight + item->getWeight()) <= (weightCapacity)) {
        inventory.push_back(item);
        weight += item->getWeight();
        statusBar->message("Added %s to inventory", item->getName().c_str());
        return true;
    } else {
        statusBar->message("%s weighs too much to add to inventory", item->getName().c_str());
        return false;
    }
}

void Player::removeItem(std::string name)
{
    std::vector<Item*>::iterator iterI;
    Item *item;
    ItemProp *prop;
    iterI = inventory.begin();

    while (iterI != inventory.end()) {
        item = *iterI;
        if (item->getName() == name) {
            prop = new ItemProp(game, item->getName());
            prop->setX(this->getX());
            prop->setY(this->getY());
            game->getEngine()->sortEntitiesByDepth();
            weight -= item->getWeight();
            inventory.erase(iterI);
        } else {
            iterI++;
        }
    }
}

void Player::equipItem(std::string name)
{
    Item *item = getInventoryItem(name);

    if (item != NULL) {
        if (!item->getEquipped()) {
            switch (item->getItemClass()) {
            case Item::armor:
                switch (item->getArmorClass()) {
                case Item::head:
                    if (headArmor != NULL) {
                        unequipItem(headArmor->getName());
                    }
                    headArmor = item;
                    defense += headArmor->getArmor();
                    break;
                case Item::torso:
                    if (torsoArmor != NULL) {
                        unequipItem(torsoArmor->getName());
                    }
                    torsoArmor = item;
                    defense += torsoArmor->getArmor();
                    break;
                case Item::hand:
                    if (handArmor != NULL) {
                        unequipItem(handArmor->getName());
                    }
                    handArmor = item;
                    defense += handArmor->getArmor();
                    break;
                case Item::foot:
                    if (footArmor != NULL) {
                        unequipItem(footArmor->getName());
                    }
                    footArmor = item;
                    defense += footArmor->getArmor();
                    break;
                default: break;
                }
                item->setEquipped(true);
                break;
            case Item::weapon:
                if (weapon != NULL) {
                    unequipItem(weapon->getName());
                }
                weapon = item;
                item->setEquipped(true);
                //damage += weapon->getDamage();
                break;
            default: break;
            }
            statusBar->message("%s was equipped", name.c_str());
        } else {
            statusBar->message("%s is already equipped", name.c_str());
        }
    } else {
        statusBar->message("%s is not in inventory", name.c_str());
    }
}

void Player::unequipItem(std::string name)
{
    Item *item = getInventoryItem(name);

    if (item != NULL) {
        if (item->getEquipped()) {
            switch (item->getItemClass()) {
            case Item::armor:
                switch (item->getArmorClass()) {
                case Item::head:
                    headArmor = NULL;
                    break;
                case Item::torso:
                    torsoArmor = NULL;
                    break;
                case Item::hand:
                    handArmor = NULL;
                    break;
                case Item::foot:
                    footArmor = NULL;
                    break;
                default: break;
                }
                defense -= item->getArmor();
                item->setEquipped(false);
                break;
            case Item::weapon:
                weapon = NULL;
                item->setEquipped(false);
                break;
            }
        }
    }
}

void Player::displayInventory()
{
    std::stringstream output;

    output << "Player Inventory: ";

    std::vector<Item*>::iterator iterI;
    Item *item;
    iterI = inventory.begin();

    while (iterI != inventory.end()) {
        item = *iterI;
        output << item->getName() << "; ";
        iterI++;
    }

    output << "Weight: " << weight << "/" << weightCapacity;

    game->getLogger()->logMessage(0, output.str().c_str());
}

}

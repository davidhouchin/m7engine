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

    attack = 5; //Physical base damage per attack
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

    Item_sword *sword = new Item_sword();
    addItem(sword);
    equipItem("sword");
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
                collide->setColor(255,0,0);
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
                collide->setColor(255,0,0);
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
                collide->setColor(255,0,0);
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
                collide->setColor(255,0,0);
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
        engine->setViewport((getX() + getXOffset()) - (engine->getScreenWidth()/2),
                            (getY() + getYOffset()) - (engine->getScreenHeight()/2),
                            engine->getScreenWidth(),
                            engine->getScreenHeight());

        //Stop viewport at edges of screen
        if (engine->getViewportX() < 0) {
            engine->setViewport(0, engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
        }
        if (engine->getViewportY() < 0) {
            engine->setViewport(engine->getViewportX(), 0, engine->getViewportW(), engine->getViewportH());
        }
        if (engine->getViewportX() > game->getLevelWidth() - engine->getViewportW()) {
            engine->setViewport(engine->getScreenWidth() - engine->getViewportW(), engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
        }
        if (engine->getViewportY() > game->getLevelHeight() - engine->getViewportH()) {
            engine->setViewport(engine->getViewportX(), engine->getScreenHeight() - engine->getViewportH(), engine->getViewportW(), engine->getViewportH());
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

void Player::addItem(Item *item)
{
    if ((this->weight + item->getWeight()) <= (this->weightCapacity)) {
        inventory.push_back(item);
        game->getLogger()->logMessage(0, "Added %s to inventory", item->getName().c_str());
    } else {
        game->getLogger()->logMessage(0, "%s weights too much to add to inventory", item->getName().c_str());
    }
}

void Player::removeItem(std::string name)
{
    std::vector<Item*>::iterator iterI;
    Item *item;
    iterI = inventory.begin();

    while (iterI != inventory.end()) {
        item = *iterI;
        if (item->getName() == name) {
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
                case Item::leg:
                    if (legArmor != NULL) {
                        unequipItem(legArmor->getName());
                    }
                    legArmor = item;
                    defense += legArmor->getArmor();
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
                attack += weapon->getDamage();
                break;
            default: break;
            }
            game->getLogger()->logMessage(0, "%s was equipped", name.c_str());
        } else {
            game->getLogger()->logMessage(0, "%s is already equipped", name.c_str());
        }
    } else {
        game->getLogger()->logMessage(0, "%s is not in inventory", name.c_str());
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
                case Item::leg:
                    legArmor = NULL;
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
                attack -= item->getDamage();
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
        output << item->getName() << ";";
        iterI++;
    }

    game->getLogger()->logMessage(0, output.str().c_str());
}

}

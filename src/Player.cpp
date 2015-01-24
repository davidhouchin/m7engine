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
    
    speed = 32; //Interval which player snaps to

    runSpeed = 5; //Time between moving while running (holding down an arrow key)
    runDelay = 20; //Time before triggering running
    runCounter = 0; //Utility variable to keep track of runSpeed
    runDelayCounter = 0; //Utility variable to keep track of runDelay
    running = false; //Is player running?

    dead = false;
    notStarted = true;
}

void Player::update()
{
    InputManager *input = game->getInput();
    CollisionManager *collision = game->getCollisionManager();
    ResourceManager *resources = game->getResourceManager();
    Engine *engine = game->getEngine();

    //Do some startup work
    if (notStarted) {
        startx = getX();
        starty = getY();
        notStarted = false;
    }

    //Key movement code
    if (!dead) {
        if (input->getKeyPressed(KEY_UP)) {
            if (!collision->getPlaceMeetingSolid(getXBBox(), getYBBox() - speed, this->id)) {
                setY(getY() - 32);
            }
        } else if (input->getKeyPressed(KEY_DOWN)) {
            if (!collision->getPlaceMeetingSolid(getXBBox(), getYBBox() + speed, this->id)) {
                setY(getY() + 32);
            }
        } else if (input->getKeyPressed(KEY_LEFT)) {
            if (!collision->getPlaceMeetingSolid(getXBBox() - speed, getYBBox(), this->id)) {
                setX(getX() - 32);
            }
        } else if (input->getKeyPressed(KEY_RIGHT)) {
            if (!collision->getPlaceMeetingSolid(getXBBox() + speed, getYBBox(), this->id)) {
                setX(getX() + 32);
            }
        }

        if ((input->getKeyReleased(KEY_UP)) ||
                (input->getKeyReleased(KEY_DOWN)) ||
                (input->getKeyReleased(KEY_LEFT)) ||
                (input->getKeyReleased(KEY_RIGHT))) {
            running = false;
        }

        if (input->getKeyHeld(KEY_UP)) {
            if (!running) {
                if (runDelayCounter < runDelay) {
                    runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if (!collision->getPlaceMeetingSolid(getXBBox(), getYBBox() - speed, this->id)) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setY(getY() - 32);
                    runCounter = 0;
                }
            }
        } else if (input->getKeyHeld(KEY_DOWN)) {
            if (!running) {
                if (runDelayCounter < runDelay) {
                     runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if (!collision->getPlaceMeetingSolid(getXBBox(), getYBBox() + speed, this->id)) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setY(getY() + 32);
                    runCounter = 0;
                }
            }
        } else if (input->getKeyHeld(KEY_LEFT)) {
            if (!running) {
                if (runDelayCounter < runDelay) {
                    runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if (!collision->getPlaceMeetingSolid(getXBBox() - speed, getYBBox(), this->id)) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setX(getX() - 32);
                    runCounter = 0;
                }
            }
        } else if (input->getKeyHeld(KEY_RIGHT)) {
            if (!running) {
                if (runDelayCounter < runDelay) {
                    runDelayCounter++;
                } else {
                    running = true;
                    runDelayCounter = 0;
                }
            } else if (!collision->getPlaceMeetingSolid(getXBBox() + speed, getYBBox(), this->id)) {
                if (runCounter < runSpeed) {
                    runCounter++;
                } else {
                    setX(getX() + 32);
                    runCounter = 0;
                }
            }
        }
    }

    //Move viewport along with character
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
    if (engine->getViewportX() > engine->getScreenWidth() - engine->getViewportW()) {
        engine->setViewport(engine->getScreenWidth() - engine->getViewportW(), engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
    }
    if (engine->getViewportY() > engine->getScreenHeight() - engine->getViewportH()) {
        engine->setViewport(engine->getViewportX(), engine->getScreenHeight() - engine->getViewportH(), engine->getViewportW(), engine->getViewportH());
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
}

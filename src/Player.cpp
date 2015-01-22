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
    
    speed = 3;
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
        if (input->getKeyHeld(KEY_UP)) {
            if (!collision->getPlaceMeetingSolid(getXBBox(), getYBBox() - speed, this->id)) {
                vSpeed = speed * -1;
                if (this->getSprite()->getName() != "playerup") {setImage(resources->getSprite("playerup")); }
            } else {
                vSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_DOWN)) {
            if (!collision->getPlaceMeetingSolid(getXBBox(), getYBBox() + speed, this->id)) {
                vSpeed = speed;
                if (this->getSprite()->getName() != "playerdown") {setImage(resources->getSprite("playerdown")); }
            } else {
                vSpeed = 0;
            }
        } else {
            vSpeed = 0;
        }

        if (input->getKeyHeld(KEY_LEFT)) {
            if (!collision->getPlaceMeetingSolid(getXBBox() - speed, getYBBox(), this->id)) {
                hSpeed = speed * -1;
                if (this->getSprite()->getName() != "playerleft") {setImage(resources->getSprite("playerleft")); }
            } else {
                hSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_RIGHT)) {
            if (!collision->getPlaceMeetingSolid(getXBBox() + speed, getYBBox(), this->id)) {
                hSpeed = speed;
                if (this->getSprite()->getName() != "playerright") {setImage(resources->getSprite("playerright")); }
            } else {
                hSpeed = 0;
            }
        } else {
            hSpeed = 0;
        }

        //Sprite animation
        if ((vSpeed != 0) || (hSpeed != 0)) {
            image->setDelay(10);
        } else {
            image->setDelay(-1);
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
    if (engine->getViewportX() > 640 - engine->getViewportW()) {
        engine->setViewport(640 - engine->getViewportW(), engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
    }
    if (engine->getViewportY() > 1920 - engine->getViewportH()) {
        engine->setViewport(engine->getViewportX(), 1920 - engine->getViewportH(), engine->getViewportW(), engine->getViewportH());
    }
}

void Player::collision(Entity *other)
{
    if ((other->getFamily() == "enemy") && (!notStarted)) {
        if (!dead) {
            dead = true;
            setImage(game->getResourceManager()->getSprite("explosion"));
            game->getEngine()->playSound(game->getResourceManager()->getSound("boom"), 0);
            xOffset = 0;
            yOffset = 0;
            hSpeed = 0;
            vSpeed = 0;
            timer[0] = (image->getMaxFrames()-1) * image->getDelay();
            setAlpha(200);
        }
    } else if (other->getName() == "coin") {
        //level->load("../resources/maps/test2.map");
    }
}

void Player::alarm(int timerNum)
{
    if (timerNum == 0) {
        setImage(game->getResourceManager()->getSprite("playerdown"));
        setOriginToImageCenter();
        setX(startx);
        setY(starty);
        dead = false;
        setAlpha(255);
    }
}
}

/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Timer
 *  Timer.cpp
 *  Purpose: Generic timer class.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Timer.h"

Timer::Timer()
{
    this->startMark  = 0;
    this->stopMark   = 0;
    this->pausedMark = 0;
    this->running    = false;
    this->paused     = false;
}

void Timer::start()
{
    if (this->running) {
        return;
    }

    this->startMark  = SDL_GetTicks();
    this->stopMark   = 0;
    this->pausedMark = 0;
    this->running    = true;
    this->paused     = false;
}

void Timer::stop()
{
    if (!this->running) {
        return;
    }

    this->stopMark = SDL_GetTicks();
    this->running  = false;
    this->paused   = false;
}

void Timer::restart()
{
    this->stop();
    this->start();
}

void Timer::pause()
{
    if (!running || paused) {
        return;
    }

    this->running    = false;
    this->paused     = true;
    this->pausedMark = (SDL_GetTicks()) - (this->startMark);
}

void Timer::unpause()
{
    if (!paused || running) {
        return;
    }

    this->running = true;
    this->paused  = false;

    this->startMark  = (SDL_GetTicks()) - (this->pausedMark);
    this->pausedMark = 0;
}

uint32_t Timer::getDelta()
{
    if (this->isRunning()) {
        return this->getCurrentTime();
    } else if (this->paused) {
        return this->pausedMark;
    } else if (this->startMark == 0) {
        return 0;
    } else {
        return (this->stopMark - this->startMark);
    }
}

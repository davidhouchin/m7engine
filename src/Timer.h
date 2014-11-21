/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Timer
 *  Timer.h
 *  Purpose: Generic timer class.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <SDL2/SDL.h>

class Timer {
public:
    Timer();

    /**
    *  Start the timer. Used as starting point.
    */
    void start();

    /**
     *  Stop the timer. Used as stopping point.
     */
    void stop();

    /**
     *  Stop the timer temporarily.
     */
    void pause();

    /**
     *  Stops, then starts the timer.
     */
    void restart();

    /**
     *  Start the timer, if paused.
     */
    void unpause();

    /**
     *  Returns whether the timer is still running.
     *  @return Whether the timer is still running.
     */
    bool isRunning() { return this->running; }

    /**
     *  Returns whether the timer is paused.
     *  @return Whether the timer is paused.
     */
    bool isPaused() { return this->paused; }

    /**
     *  Returns the timer's difference in milliseconds.
     *  @return The delta time in milliseconds.
     */
    uint32_t getDelta();

    /**
     *  Returns the timer's difference in milliseconds.
     *  @return The delta time in milliseconds.
     */
    uint32_t getDeltaMS() { return (this->getDelta() % 1000); }

    /**
     *  Returns the timer's difference in seconds.
     *  @return The delta time in seconds.
     */
    uint32_t getDeltaS() { return (this->getDelta() / 1000); }

    /**
     *  Returns the difference between starting and now.
     *  @return The difference between starting and now.
     */
    uint32_t getCurrentTime() { return (SDL_GetTicks()) - (this->startMark); }

protected:
    uint32_t startMark, stopMark, pausedMark;

    bool running, paused;
};

#endif

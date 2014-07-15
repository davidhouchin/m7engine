/**
 *  Timer
 *  Timer.h
 *  Purpose: General purpose timer class.
 *  @author Alex Dantas and David Houchin
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
    bool isRunning();

    /**
     *  Returns whether the timer is paused.
     *  @return Whether the timer is paused.
     */
    bool isPaused();

    /**
     *  Returns the timer's difference in milliseconds.
     *  @return The delta time in milliseconds.
     */
    uint32_t getDelta();

    /**
     *  Returns the timer's difference in milliseconds.
     *  @return The delta time in milliseconds.
     */
    uint32_t getDeltaMS();

    /**
     *  Returns the timer's difference in seconds.
     *  @return The delta time in seconds.
     */
    uint32_t getDeltaS();

    /**
     *  Returns the difference between starting and now.
     *  @return The difference between starting and now.
     */
    uint32_t getCurrentTime();

protected:
    uint32_t startMark;
    uint32_t stopMark;
    uint32_t pausedMark;

    bool running;
    bool paused;
};

#endif

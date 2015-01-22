/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Input Manager
 *  InputManager.h
 *  Purpose: Manager to access and handle keyboard and mouse input.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef INPUTMANAGER_H
#define	INPUTMANAGER_H

#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "Logger.h"
#include "InputKeyDefinitions.h"

namespace M7engine {
class InputManager {
public:
    /**
     *  Returns a pointer to the input manager.
     *  @return Pointer to input manager.
     */
    static InputManager* getInstance();

    virtual ~InputManager();

    /**
     *  Initializes input manager.
     */
    bool init();

    /**
     *  Main update function for input manager.
     */
    void update();

    /**
     *  Returns the current X position of the mouse pointer.
     *  @return The current X position of the mouse pointer.
     */
    int getMouseX() { return this->mouseX; }

    /**
     *  Returns the current Y position of the mouse pointer.
     *  @return The current Y position of the mouse pointer.
     */
    int getMouseY() { return this->mouseY; }

    /**
     *  Returns whether passed mouse button was pressed during the last cycle.
     *  @param button Button to test.
     *  @return Whether passed mouse button was pressed during the last cycle.
     */
    bool getMousePressed(int button) { return mouseKeyStates[button] & KEY_PRESS; }

    /**
     *  Returns whether passed mouse button was released during the last cycle.
     *  @param button Button to test.
     *  @return Whether passed mouse button was released during the last cycle.
     */
    bool getMouseReleased(int button) { return mouseKeyStates[button] & KEY_RELEASE; }

    /**
     *  Returns whether passed mouse button has been held during current and last cycle.
     *  @param button Button to test.
     *  @return Whether passed mouse button has been held during current and last cycle.
     */
    bool getMouseHeld(int button) { return mouseKeyStates[button] & KEY_HELD; }

    /**
     *  Returns whether passed mouse button has not been pushed during current and last cycle.
     *  @param button Button to test.
     *  @return Whether passed mouse button has not been pushed during current and last cycle.
     */
    bool getMouseOpen(int button) { return mouseKeyStates[button] & KEY_OPEN; }

    /**
     *  Returns whether passed key has been pressed during the last cycle.
     *  @param key Key to test.
     *  @return Whether passed key has been pressed during the last cycle.
     */
    bool getKeyPressed(int key) { return keyStates[key] & KEY_PRESS; }

    /**
     *  Returns whether passed key has been released during the last cycle.
     *  @param key Key to test.
     *  @return Whether passed key has been released during the last cycle.
     */
    bool getKeyReleased(int key) { return keyStates[key] & KEY_RELEASE; }

    /**
     *  Returns whether passed key has been held during current and last cycle.
     *  @param key Key to test.
     *  @return Whether passed key has been held during current and last cycle.
     */
    bool getKeyHeld(int key) { return keyStates[key] & KEY_HELD; }

    /**
     *  Returns whether passed key has not been pushed during current and last cycle.
     *  @param key Key to test.
     *  @return Returns whether passed key has not been pushed during current and last cycle.
     */
    bool getKeyOpen(int key) { return keyStates[key] & KEY_OPEN; }

    /**
     *  Returns the last key pressed.
     *  @return The last key pressed.
     */
    int getKeyLast() { return keyLast; }

    void startTextInput() { isWatchingText = true; }
    void stopTextInput() { isWatchingText = false; }
    std::string getTextString() { return textInput; }
    void eraseTextInput() { textInput = ""; }

    /**
     *  Returns if the user has initiated an SDL_QUIT event.
     *  @return Whether an SDL_QUIT event has occurred.
     */
    bool hasQuit() {return quit; }

    /**
     *  Initiates a quit event.
     */
    void setQuit() { quit = true; }

private:
    InputManager();
    static InputManager* managerInstance;
    bool quit, isWatchingText;

    std::string textInput;

    int mouseX, mouseY, mouseZ;
    const uint8_t* keyboardState;
    uint32_t mouseState;

    bool mouseKeys[MOUSE_MAX];
    bool oldMouseKeys[MOUSE_MAX];
    int mouseKeyStates[MOUSE_MAX];

    bool keys[KEYBOARD_SIZE];
    bool oldKeys[KEYBOARD_SIZE];
    int keyStates[KEYBOARD_SIZE];
    int keyLast;

    enum KEYSTATE {
        KEY_PRESS = 1, KEY_RELEASE = 2, KEY_HELD = 4, KEY_OPEN = 8
    };
};
}

#endif

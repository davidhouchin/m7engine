/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
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
#include <allegro5/allegro.h>
#include "Logger.h"

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
     *  Returns the current Z position of the mouse pointer.
     *  @return The current Z position of the mouse pointer.
     */
    int getMouseZ() { return this->mouseZ; }
    /**
     *  Returns the current X position of the mouse pointer.
     *  @return The current X position of the mouse pointer.
     */
    int getMouseDX() { return this->mouseDX; }
    /**
     *  Returns the current Y position of the mouse pointer.
     *  @return The current Y position of the mouse pointer.
     */
    int getMouseDY() { return this->mouseDY; }
    /**
     *  Returns the current Z position of the mouse pointer.
     *  @return The current Z position of the mouse pointer.
     */
    int getMouseDZ() { return this->mouseDZ; }
    /**
     *  Returns the number of detected buttons on the mouse.
     *  @return The number of detected buttons on the mouse.
     */
    int getMouseKeyNum() { return al_get_mouse_num_buttons(); }
    /**
     *  Returns the current state of the passed mouse button.
     *  @param id ID of entity to find.
     *  @return Pointer of entity, if found.
     */
    bool getMouseState(int button) { return al_mouse_button_down(&mouseState, button); }
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
     *  Returns the current state of the passed key.
     *  @param key Key to test.
     *  @return The state of the passed key.
     */
    bool getKeyState(int key) { return al_key_down(&keyboardState, key); }
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

private:
    InputManager();
    static InputManager* managerInstance;
    int mouseX, mouseY, mouseZ, mouseDX, mouseDY, mouseDZ;
    ALLEGRO_EVENT_QUEUE *keyboardQueue;
    ALLEGRO_EVENT_QUEUE *mouseQueue;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;
    int keyLast;
    bool *mouseKeys;
    bool *oldMouseKeys;
    int *mouseKeyStates;
    bool keys[ALLEGRO_KEY_MAX];
    bool oldKeys[ALLEGRO_KEY_MAX];
    int keyStates[ALLEGRO_KEY_MAX];
    enum KEYSTATE {
        KEY_PRESS = 1, KEY_RELEASE = 2, KEY_HELD = 4, KEY_OPEN = 8
    };
};
}

#endif

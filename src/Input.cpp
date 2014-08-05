/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Input Manager
 *  InputManager.cpp
 *  Purpose: Manager to access and handle keyboard and mouse input.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Input.h"

namespace M7engine {
InputManager* InputManager::managerInstance = NULL;

InputManager* InputManager::getInstance()
{
    if (!managerInstance) {
        managerInstance = new InputManager;
    }

    return managerInstance;
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::init()
{
    quit = false;

    mouseX = 0;
    mouseY = 0;

    for (int i = 0; i < KEYBOARD_SIZE; ++i) {
        keys[i] = false;
        oldKeys[i] = false;
    }

    for (int i = 0; i < MOUSE_MAX; ++i) {
        mouseKeys[i] = false;
        oldMouseKeys[i] = false;
    }

    isWatchingText = false;
    textInput = "";

    return true;
}

void InputManager::update()
{
    for (int i = 0; i < KEYBOARD_SIZE; ++i) {
        oldKeys[i] = keys[i];
    }

    for (int i = 0; i < MOUSE_MAX; ++i) {
        oldMouseKeys[i] = mouseKeys[i];
    }

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
        case SDL_KEYDOWN:
            keyboardState = SDL_GetKeyboardState(NULL);
            keys[ev.key.keysym.scancode] = true;
            keyLast = ev.key.keysym.scancode;
            Logger::getInstance()->logMessage(98, "Key %i Pressed", ev.key.keysym.scancode);
            //Handle backspace and copy/paste for text input
            if (isWatchingText) {
                if (ev.key.keysym.sym == SDLK_BACKSPACE && textInput.length() > 0) {
                    textInput.pop_back();
                }
                else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                    textInput = SDL_SetClipboardText(textInput.c_str());
                }
                else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                    textInput = SDL_GetClipboardText();
                }
            }
            break;
        case SDL_KEYUP:
            keyboardState = SDL_GetKeyboardState(NULL);
            keys[ev.key.keysym.scancode] = false;
            keyLast = ev.key.keysym.scancode;
            Logger::getInstance()->logMessage(98, "Key %i Released", ev.key.keysym.scancode);
            break;
        case SDL_MOUSEMOTION:
            mouseX = ev.motion.x;
            mouseY = ev.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseState = SDL_GetMouseState(&mouseX, &mouseY);
            switch (ev.button.button) {
            case SDL_BUTTON_LEFT: mouseKeys[MOUSE_LEFT] = true; break;
            case SDL_BUTTON_RIGHT: mouseKeys[MOUSE_RIGHT] = true; break;
            default: break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            mouseState = SDL_GetMouseState(&mouseX, &mouseY);
            switch (ev.button.button) {
            case SDL_BUTTON_LEFT: mouseKeys[MOUSE_LEFT] = false; break;
            case SDL_BUTTON_RIGHT: mouseKeys[MOUSE_RIGHT] = false; break;
            default: break;
            }
            break;
        case SDL_MOUSEWHEEL: break;
        case SDL_QUIT: quit = true; break;
        case SDL_TEXTINPUT:
            if (isWatchingText) {
                //Make sure copy and pasting is not happening..
                if (!((ev.text.text[0] == 'c' || ev.text.text[0] == 'C') &&
                      (ev.text.text[0] == 'v' || ev.text.text[0] == 'V') &&
                      SDL_GetModState() & KMOD_CTRL)) {
                    textInput += ev.text.text;
                }
            }
        default: break;
        }
    }

    for (int i = 0; i < KEYBOARD_SIZE; ++i) {
        if (keys[i] && !oldKeys[i]){ keyStates[i] = KEY_PRESS; }
        if (!keys[i] && oldKeys[i]){ keyStates[i] = KEY_RELEASE; }
        if (keys[i] && oldKeys[i]){ keyStates[i] = KEY_HELD; }
        if (!keys[i] && !oldKeys[i]){ keyStates[i] = KEY_OPEN; }
    }

    for (int i = 0; i < MOUSE_MAX; ++i) {
        if (mouseKeys[i] && !oldMouseKeys[i]){ mouseKeyStates[i] = KEY_PRESS; }
        if (!mouseKeys[i] && oldMouseKeys[i]){ mouseKeyStates[i] = KEY_RELEASE; }
        if (mouseKeys[i] && oldMouseKeys[i]){ mouseKeyStates[i] = KEY_HELD; }
        if (!mouseKeys[i] && !oldMouseKeys[i]){ mouseKeyStates[i] = KEY_OPEN; }
    }
}
}

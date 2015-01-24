/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  LevelEditor
 *  LevelEditor.h
 *  Purpose: Main level editor class.
 *  @author David Houchin
 *  @version 1.0 1/24/15
 */

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "Game.h"
#include "Level.h"

namespace SampleGame {
class EditorWindow : public Window {
private:
    Game *game;
public:
    EditorWindow(Game *game, int x, int y, int width, int height);
    void handleInput(std::string name);
};

class LevelEditor {
private:
    Game *game;
    Window *editorWindow;
public:
    LevelEditor(Game *game);
    Window* getWindow() {return this->editorWindow;}
};
}

#endif

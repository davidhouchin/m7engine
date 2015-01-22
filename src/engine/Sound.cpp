/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Sound Manager
 *  SoundManager.cpp
 *  Purpose: Manager to handle sound sample modification and playback.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "Sound.h"

namespace M7engine {
Sound::Sound()
{
    sound = NULL;
    filename = "";
}

Sound::~Sound()
{
    Mix_FreeChunk(sound);
}

bool Sound::loadSound(const char* filename)
{
    Logger::getInstance()->logMessage(0, "Sound '%s' loading chunk: '%s'", name.c_str(), filename);
    if (sound != NULL) {
        Mix_FreeChunk(sound);
        sound = NULL;
    }

    sound = Mix_LoadWAV(filename);
    if (!sound) {
        Logger::getInstance()->logError(0, "Sound failed to load chunk: %s", Mix_GetError());
        return false;
    } else {
        return true;
    }
}

void Sound::setSound(Mix_Chunk* sound)
{
    if (sound != NULL) {
        this->sound = sound;
    }
}
}

/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Sound Manager
 *  SoundManager.h
 *  Purpose: Manager to handle sound sample modification and playback.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef SOUNDMANAGER_H
#define	SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>

#include "Logger.h"

namespace M7engine {
class Sound {
public:
    Sound();
    virtual ~Sound();

    /**
     *  Load a sound from the given filename.
     *  @param *filename Char array containing filename.
     *  @return Whether load was successful.
     */
    bool loadSound(const char *filename);

    /**
     *  Directly set sound using a Mix_Chunk.
     *  @param *sound Mix_Chunk to use.
     */
    void setSound(Mix_Chunk* sound);

    /**
     *  Returns the Mix_Chunk being used.
     *  @return Mix_Chunk being used.
     */
    Mix_Chunk* getSound() { return sound; }

    /**
     *  Returns the resource name of the font.
     *  @return String containing name.
     */
    std::string getName(){ return this->name; }

    /**
     *  Set the resource name of the font.
     *  @param name String containing name to set.
     */
    void setName(std::string name) { this->name = name; }

private:
    Mix_Chunk* sound;
    const char *filename;
    std::string name;
};
}

#endif

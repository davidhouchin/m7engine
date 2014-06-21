/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Configuration Reader
 *  ConfigReader.h
 *  Purpose: Reads a configuration file to set engine options.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <stdio.h>
#include <cstring>
#include <string>
#include <allegro5/allegro.h>
#include "Logger.h"

namespace M7engine {
class ConfigReader {
public:
    ConfigReader();
    virtual ~ConfigReader();

    /**
     *  Load a configuration file into memory.
     *  @param *filename Path to the file to load.
     *  @return A bool if successful.
     */
    bool loadConfig(const char *filename);

    /**
     *  Retrieve an int value from a loaded configuration file.
     *  @param *section The section to retrieve value from.
     *  @param *key The specific key to retrieve value from.
     *  @return An int containing the value of the key.
     */
    int getInt(const char *section, const char *key);
    /**
     *  Retrieve a bool value from a loaded configuration file.
     *  @param *section The section to retrieve value from.
     *  @param *key The specific key to retrieve value from.
     *  @return An bool containing the value of the key.
     */
    bool getBool(const char *section, const char *key);
    /**
     *  Retrieve char value from a loaded configuration file.
     *  @param *section The section to retrieve value from.
     *  @param *key The specific key to retrieve value from.
     *  @return A char array containing the value of the key.
     */
    const char* getChar(const char *section, const char *key);

private:
    ALLEGRO_CONFIG* engineConfig;
};
};

#endif

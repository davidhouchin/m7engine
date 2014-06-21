/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Configuration Reader
 *  ConfigReader.cpp
 *  Purpose: Reads a configuration file to set engine options.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#include "ConfigReader.h"

namespace M7engine {
ConfigReader::ConfigReader() {
    engineConfig = NULL;
}

ConfigReader::~ConfigReader() {
    al_destroy_config(engineConfig);
}

bool ConfigReader::loadConfig(const char *filename) {
    Logger::getInstance()->logMessage(0, "ConfigReader loading config file: '%s'", filename);

    engineConfig = al_load_config_file(filename);
    if (!engineConfig) {
        Logger::getInstance()->logError(0, "ConfigReader failed to load config file: '%s'", filename);
        return false;
    } else {
        return true;
    }
}

int ConfigReader::getInt(const char *section, const char *key) {
    if (!engineConfig) {
        Logger::getInstance()->logError(0, "ConfigReader failed to get value, no config file");

        return NULL;
    } else {
        int value;
        value = atoi(al_get_config_value(engineConfig, section, key));
        return value;
    }
}

bool ConfigReader::getBool(const char *section, const char *key) {
    if (!engineConfig) {
        Logger::getInstance()->logError(0, "ConfigReader failed to get value, no config file");

        return NULL;
    } else {
        int value;
        value = atoi(al_get_config_value(engineConfig, section, key));

        if (value != 0) { return true; }
        else { return false; }
    }
}

const char* ConfigReader::getChar(const char *section, const char *key)
{
    if (!engineConfig) {
        Logger::getInstance()->logError(0, "ConfigReader failed to get value, no config file");
        return NULL;
    } else {
        return al_get_config_value(engineConfig, section, key);
    }
}
}

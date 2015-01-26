/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Configuration Reader
 *  ConfigReader.h
 *  Purpose: Reads a configuration file and stores the values in a map for retrieval.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <map>

#include "Logger.h"
#include "Utilities.h"

#define COMMENT_CHAR '#'
#define SECTION_BEGIN_CHAR '['
#define SECTION_END_CHAR ']'

namespace M7engine {
class ConfigReader {
public:
    ConfigReader();
    virtual ~ConfigReader();

    /**
     *  @brief Load a configuration file into memory, and then parses
     *  the contents into mappable values.
     *  @param *filename Path to the file to load.
     *  @return A bool if successful.
     */
    bool loadConfig(std::string filename);

    /**
     *  @brief Reloads configuration file. Same as calling loadConfig,
     *  but uses previous filename.
     *  @return A bool if successful.
     */
    bool reloadConfig();

    void clearConfig() { config.clear(); }

    /**
     *  @brief Check if a specific key exists.
     *  @param section The section to check for key.
     *  @param key The specific key to check the existence of.
     *  @return A bool if successful.
     */
    bool hasKey(std::string section, std::string key);

    /**
     *  @brief Check if a section exists.
     *  @param section The section to check for key.
     *  @return A bool if successful.
     */
    bool hasSection(std::string section);

    /**
     *  @brief Returns a string containing the first section stored.
     *  @return A string containing the name of the first section.
     */
    std::string getFirstSection();

    /**
     *  @brief Returns a string of the section stored after the specified section.
     *  @param section The section to check after.
     *  @return A string containing the name of the next section.
     */
    std::string getNextSection();

    /**
     *  @brief Retrieve an int value from a loaded configuration file.
     *  @param section The section to retrieve value from.
     *  @param key The specific key to retrieve value from.
     *  @return An int containing the value of the key.
     */
    int getInt(std::string section, std::string key);

    /**
     *  @brief Retrieve an int value from a loaded configuration file.
     *  @param section The section to retrieve value from.
     *  @param key The specific key to retrieve value from.
     *  @param def The default value to return if the key is not found.
     *  @return An int containing the value of the key.
     */
    int getInt(std::string section, std::string key, int def);

    /**
     *  @brief Retrieve a bool value from a loaded configuration file.
     *  @param section The section to retrieve value from.
     *  @param key The specific key to retrieve value from.
     *  @return An bool containing the value of the key.
     */
    bool getBool(std::string section, std::string key);

    /**
     *  @brief Retrieve a bool value from a loaded configuration file.
     *  @param section The section to retrieve value from.
     *  @param key The specific key to retrieve value from.
     *  @param def The default value to return if the key is not found.
     *  @return An bool containing the value of the key.
     */
    bool getBool(std::string section, std::string key, bool def);

    /**
     *  @brief Retrieve char value from a loaded configuration file.
     *  @param section The section to retrieve value from.
     *  @param key The specific key to retrieve value from.
     *  @return A stringcontaining the value of the key.
     */
    std::string getString(std::string section, std::string key);

    /**
     *  @brief Retrieve char value from a loaded configuration file.
     *  @param section The section to retrieve value from.
     *  @param key The specific key to retrieve value from.
     *  @param def The default value to return if the key is not found.
     *  @return A string containing the value of the key.
     */
    std::string getString(std::string section, std::string key, std::string def);

private:
    std::string filename;
    std::string resolvePath;

    //Stored in format section->key->value.
    typedef std::map<std::string, std::string> innerMap;
    std::map<std::string, innerMap> config;

    //Iterator for cycling through sections.
    std::map<std::string, innerMap>::iterator mapIter;
};
};

#endif

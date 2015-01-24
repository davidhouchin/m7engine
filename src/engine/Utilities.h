/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
* For more information, see COPYING.
*/
/**
 *  Utilities
 *  Utilities.h
 *  Purpose: General purpose utility functions.
 *  @author David Houchin
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>

namespace M7engine {
/**
 *  @brief Convert the given int to a string.
 *  @param num Int to convert.
 *  @return The converted string.
 */
std::string intToString(int num);

/**
 *  @brief Convert the given string to an int.
 *  @param text String to convert.
 *  @return The converted int.
 */
int stringToInt(std::string text);

/**
 * @brief Snaps the given int to the next lowest grid value.
 * @param num Int to snap.
 * @param grid Width of grid.
 * @return The next lowest grid value.
 */
int snapToGrid(int num, int grid);

/**
 *  @brief Remove all whitespace from the given string.
 *  @param str The string to empty.
 *  @return The emptied string.
 */
std::string& removeWhitespace(std::string &str);

/**
 *  @brief Split the given string into two based on a delimiter.
 *  @param str The string to split.
 *  @param delim The character to treat as the delimiter.
 *  @return A vector containing the 2 new strings.
 */
std::vector<std::string> split(const std::string& str, char delim);

/**
 * @brief Split the given string into a vector of strings based on a delimeter.
 * @param str The string to split.
 * @param delim The character to treat as the delimiter.
 * @return A vector containing the individual strings.
 */
std::vector<std::string> chunkify(const std::string& str, const char& delim);
};

#endif

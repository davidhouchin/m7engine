/**
 *  Utilities
 *  Utilities.h
 *  Purpose: General purpose utility functions.
 *  @author Alex Dantas and David Houchin
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
 *  Convert the given int to a string.
 *  @param num Int to convert.
 *  @return The converted string.
 */
std::string intToString(int num);

/**
 *  Convert the given string to an int.
 *  @param text String to convert.
 *  @return The converted int.
 */
int stringToInt(std::string text);

/**
 *  Remove all whitespace from the given string.
 *  @param &str The string to empty.
 *  @return The emptied string.
 */
std::string& removeWhitespace(std::string &str);

/**
 *  Split the given string into two based on a delimiter.
 *  @param &str The string to split.
 *  @param delim The character to treat as delimiter.
 *  @return A vector containing the 2 new strings.
 */
std::vector<std::string> split(const std::string& str, char delim);

std::vector<std::string> chunkify(const std::string& str, const char& delim);
};

#endif

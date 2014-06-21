/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Logger
 *  Logger.h
 *  Purpose: Class to handle logging output.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */


#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

namespace M7engine {
class Logger {
public:
    /**
     *  Returns the static instance of the logger.
     *  @return Pointer to logger.
     */
    static Logger* getInstance();

    virtual ~Logger();

    /**
     *  Set the level determining amount of reporting.
     *  @param level Int of reporting level. Lower value is less logging.
     */
    void setLoggingLevel(int level) { logLevel = level; }
    /**
     *  Set file to use as log.
     *  @param *file Char array containing filename.
     */
    bool setLogFile(const char *file);

    /**
     *  Log a message with default coloring. Accepts printf style variable arguments.
     *  @param level Reporting level message is sent at.
     *  @param *message Char array containing message.
     */
    void logMessage(int level, const char *message, ...);
    /**
     *  Log a message with specified coloring. Accepts printf style variable arguments.
     *  @param level Reporting level message is sent at.
     *  @param *message Char array containing message.
     *  @param color ALLEGRO_COLOR defining text color.
     */
    void logMessage(int level, const char *message, ALLEGRO_COLOR color, ...);

    /**
     *  Log an error with default coloring. Accepts printf style variable arguments.
     *  @param level Reporting level error is sent at.
     *  @param *message Char array containing error.
     */
    void logError(int level, const char *message, ...);
    /**
     *  Log an error with specified coloring. Accepts printf style variable arguments.
     *  @param level Reporting level error is sent at.
     *  @param *message Char array containing error.
     */
    void logError(int level, const char *message, ALLEGRO_COLOR color, ...);

private:
    Logger();
    int logLevel;
    const char *filename;
    std::ofstream logFile;
    static Logger* loggerInstance;
};
};

#endif

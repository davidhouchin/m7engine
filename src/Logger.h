/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the ZLib license.
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
#include <SDL2/SDL.h>

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
    bool setLogFile(const char* file);

    /**
     *  Log a message with default coloring. Accepts printf style variable arguments.
     *  @param level Reporting level message is sent at.
     *  @param message String containing message.
     */
    void logMessage(int level, std::string message, ...);

    /**
     *  Log an error with default coloring. Accepts printf style variable arguments.
     *  @param level Reporting level error is sent at.
     *  @param message String containing error.
     */
    void logError(int level, std::string message, ...);

private:
    Logger();
    static Logger* loggerInstance;

    int logLevel;
    const char* filename;

    std::ofstream logFile;
};
};

#endif

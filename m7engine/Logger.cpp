/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "Logger.h"

namespace M7engine
{
Logger::Logger(const char *file)
{
	logLevel = 0;
	filename = file;
	remove(filename);
}

Logger::~Logger()
{
	logFile.close();
}

bool Logger::setLogFile(const char *file)
{
	filename = file;
	logFile.open(filename);
	if (!logFile.is_open())
	{
		return false;
	}
	logFile.close();
}

void Logger::logMessage(int level, const char *message, ...)
{
	if (level <= logLevel)
	{
		char buffer[99];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, message, args);
		va_end(args);

		fprintf(stdout, "%s\n", buffer);

		logFile.open(filename, std::ios::app);
		logFile << buffer << "\n";
		logFile.close();
	}
}

void Logger::logMessage(const char *message, int level, ALLEGRO_COLOR color)
{
	if (level <= logLevel)
	{
		char buffer[99];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, message, args);
		va_end(args);

		fprintf(stdout, "%s\n", buffer);

		logFile.open(filename, std::ios::app);
		logFile << buffer << "\n";
		logFile.close();
	}
}

void Logger::logError(const char *message, int level)
{
	if (level <= logLevel)
	{
		char buffer[99];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, message, args);
		va_end(args);

		fprintf(stderr, "%s\n", buffer);

		logFile.open(filename, std::ios::app);
		logFile << buffer << "\n";
		logFile.close();
	}
}

void Logger::logError(const char *message, int level, ALLEGRO_COLOR color)
{
	if (level <= logLevel)
	{
		char buffer[99];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, message, args);
		va_end(args);

		fprintf(stderr, "%s\n", buffer);

		logFile.open(filename, std::ios::app);
		logFile << buffer << "\n";
		logFile.close();
	}
}
}
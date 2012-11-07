#include "Logger.h"
#include <cstdarg>

/*
sourceName will be added to every message from here to identify the message.
Name of class is recommended.

TriggerLevel should of course in a complete system be controlled by config file.

*/
Logger::Logger(const std::string &sourceName,Level triggerLevel)
{
	Logger::sourceName=sourceName;
	Logger::triggerLevel=triggerLevel;
	Logger::currentLevel=triggerLevel;
}

Logger::~Logger(void)
{
}
/**
Simple string based log appender. Use stringstream or boost::format to make your message and send it here.
*/
void Logger::Log(Level level,const std::string &message){
	if(level >= triggerLevel){
		LogSys::Instance().Write(sourceName,level,message);
	}
}
/**
Varargs type log appender.
Against my better judgement, but it seems to be expected.
NOTE: Only handles messages (including inserted variable args) of length less than 1024!
*/
void Logger::Logf(Level level,const char* message, ...){
	if(level >= triggerLevel){
		va_list varArgs; 
		va_start(varArgs, message);
		char destBuffer[1024];
		vsprintf_s(destBuffer,1024 * sizeof(char),message,varArgs);
		LogSys::Instance().Write(sourceName,level,destBuffer);
	}
}

void Logger::SetLogLevel( Level newLevel )
{
	if(currentLevel != newLevel && triggerLevel != newLevel)
	{
		currentLevel = newLevel;
		triggerLevel = newLevel;
	}
}

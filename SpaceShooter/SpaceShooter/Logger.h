/********************************************************************
	created:	2012/01
	filename: 	Logger.h

	author:		Kristian Skarseth, Peder Thorup, Kjetil Raaen
	
	purpose:	Logger class. This is the class you create an object with in
				each class you want logging. All log lines then goes trough this
				into the LogSys class which handles the output.
*********************************************************************/

#ifndef Logger_H
#define Logger_H

#include "LogSys.h"
#include <string>
#include <sstream>
class Logger
{
private:
	std::string sourceName;
	Level triggerLevel;
	Level currentLevel;
	std::stringstream buffer;
public:
	Logger(const std::string &sourceName,Level triggerLevel);
	~Logger(void);
	void SetLogLevel(Level newLevel);
	void Log(Level level,const std::string &message);
	void Logf(Level level,const char* message, ...);

	//Stream functionality for more modern approach.
	Logger& operator<<(Level level){
		currentLevel=level;
		return *this;
	}
	Logger& operator<<( std::ostream& (*f)(std::ostream&) ){
		if(currentLevel >= triggerLevel)
		{
			LogSys::Instance().Write(sourceName,currentLevel,buffer.str());
			buffer.str("");
		}
		return *this;
	}
	template<typename T> Logger& operator<<(const T message){
		if(currentLevel >= triggerLevel)
		{
			buffer << message;
		}
		return *this;
	}
};

#endif // Logger_H
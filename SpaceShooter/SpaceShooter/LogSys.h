/********************************************************************
	created:	2012/01
	filename: 	LogSys.h

	author:		Kristian Skarseth, Peder Thorup, Kjetil Raaen
	
	purpose:	Logger class. This class is a singleton which gets the 
				log lines from the Logger class and takes care of writing
				them to file or console.
*********************************************************************/

#ifndef LogSys_H
#define LogSys_H

#include <string>
#include <fstream>
enum Level{
	INFO,WARN,ERRORX,CRITICAL
};
/*
Main logsystem class. All calls will be direcetd through this singleton.
*/
class LogSys
{
public: 
	static LogSys& Instance();
	void Write(const std::string &source,Level level,const std::string &message);
private:  LogSys(const std::string &fileName); // ctor hidden  
		   LogSys(LogSys const&); // copy ctor hidden  
		   LogSys& operator=(LogSys const&); // assign op. hidden  
		   ~LogSys(); // dtor hidden
		   static const std::string SEPARATOR;
		   bool toConsole; // set to false to stop logging to console.
		   std::fstream fileOut;
};

;
static std::string levelNames[] = {
	"Info", "Warn", "Error", "Critical" 
};

#endif // LogSys_H
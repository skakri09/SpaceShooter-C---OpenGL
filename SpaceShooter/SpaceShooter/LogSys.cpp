#include "LogSys.h"
#include "Windows.h"
#include <sstream>
#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iomanip>
using namespace std;

LogSys::LogSys(const std::string &fileName)
{
	LogSys::toConsole= true;// set to false to stop logging to console.
	fileOut.open(fileName,std::fstream::out | std::fstream::app);
}


LogSys::~LogSys(void)
{
	fileOut.close();
}


LogSys& LogSys::Instance()
{
	// Why this works: a static variable starts existing when its codeline is executed for the 
	// first time, but does NOT stop existing at the normal end of scope. Thus, by putting the 
	// instance variable in this function, not in the class itself, it won't be made until its 
	// used. But still, we don't need to do manual clean up after it, as we would be the case 
	// with the regular "pointer to instance object as class variable" approach. Neat, eh?


	// Also, parameters should ofcourse be in a config file.
	static LogSys instance("..//log//log.txt");
	return instance;  
}  

const std::string LogSys::SEPARATOR=" ; ";

/**
write everything, remember timestamp 
*/
void LogSys::Write(const std::string &source,Level level,const std::string &message){
#define logging
#ifdef logging

	std::stringstream result;
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();

	std::string nowTime = to_iso_extended_string(now);
	std::string::iterator iter = nowTime.begin();

	while(*iter != 'T')
	{
		nowTime.erase(iter);

	}
	nowTime.erase(iter);
	nowTime.pop_back();
	nowTime.pop_back();
	nowTime.pop_back();

	result << nowTime << SEPARATOR << source << SEPARATOR << levelNames[level] << SEPARATOR << message;
	fileOut << result.str() << std::endl;
	if(toConsole)
		std::cout << result.str() << std::endl;
	//std::cout << setw(12) << left << source.c_str()  << message << std::endl;

#endif
}
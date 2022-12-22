#pragma once

#include <exception>
#include <ctime>
#include <string>

class ErrorTracker
{
private:
    std::string LogFileName;
public:
	ErrorTracker(){};
    void setLogName(std::string LogName){LogFileName = LogName;}
    void write_log(std::string what, bool Critacal);
};

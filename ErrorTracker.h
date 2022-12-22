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
    ErrorTracker(std::string LogName);
    void write_log(std::string what, bool Critacal);
};

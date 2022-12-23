#pragma once

#include <exception>
#include <ctime>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

class ErrorTracker
{
private:
    std::string LogFileName;
public:
	ErrorTracker(){};
    void setLogName(std::string LogName){LogFileName = LogName;}
    void write_log(std::string what, bool Critical);
	~ErrorTracker(){};
};

class server_error: public std::invalid_argument {
private:
bool State = false;
public:
explicit server_error (const std::string& what_arg, bool critical = false):
std::invalid_argument(what_arg) {State = critical;}
explicit server_error (const char* what_arg,  bool critical = false):
std::invalid_argument(what_arg) {State = critical;}
bool getState() const {return State;}
};

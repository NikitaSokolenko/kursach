#include "ErrorTracker.h"
#include <exception>
#include <ctime>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <iostream>

ErrorTracker::ErrorTracker(std::string LogName)
{
    LogFileName = LogName;
}

void ErrorTracker::write_log(std::string what, bool Critical)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    std::ofstream log(LogFileName);
	if(!log.good()){
		exit(1);} 
    char err_buf[1024];
    std::string err_msg;
    if (Critical){
    err_msg = std::string(dt)+" "+what + " Критическая\n";}
    else {err_msg = std::string(dt)+" "+what + " Штатная\n";}
    strcpy(err_buf, err_msg.c_str());
    log.write(err_buf,sizeof(err_buf));
    log.close();
}

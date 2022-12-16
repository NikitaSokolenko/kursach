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

void ErrorTracker::write_log(std::string what)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    std::ofstream log(LogFileName);
    char err_buf[100];
    std::string err_msg = std::string(dt)+" "+what;
    strcpy(err_buf, err_msg.c_str());
    log.write(err_buf,sizeof(err_buf));
    log.close();
}

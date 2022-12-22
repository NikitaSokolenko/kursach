#pragma once
#include <string>
#include <map>

using namespace std;

class Opts
{
private:
    string DataBaseName = "/home/stud/C++Projects/kursach/DB.txt";
    string LogFileName = "log.txt";
    int Port = 33333;
    char sep = ':';
    void usage(const char* progName); //вывод подсказки и останов
public:
    Opts(int argc, char **argv);
    map <string,string> DataBaseP;
    string getDataBaseName()
    {
        return DataBaseName;
    }
    string getLogFileName()
    {
        return LogFileName;
    }
    int getPort()
    {
        return Port;
    }
    bool CheckFiles();
};

#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>
#include <iostream>
#include <boost/algorithm/string.hpp>

class DB
{
private:
    char sep = ' ';
public:
    DB(std::string DBName)
    {
        std::ifstream file(DBName);
        std::string Pair;
        while(getline(file, Pair)) {
            DataBaseP[Pair.substr(0,Pair.find(sep))] = Pair.substr(Pair.find(sep)+1);
            //DataBaseP.insert(make_pair(Pair, Pair));
        }
        file.close();
    }
    std::map <std::string,std::string> DataBaseP;
    bool IDcheck(std::string login)
    {
        for (std::map<std::string, std::string>::iterator it=DataBaseP.begin(); it!=DataBaseP.end(); ++it) {
            std::cout << it->first << " => " << it->second << '\n';
        }
        return DataBaseP.count(login) == 1;
    }
};

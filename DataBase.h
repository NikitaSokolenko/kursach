#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>

class DB
{
private:
    char sep = ':';
public:
    DB(std::string DBName)
    {
        std::ifstream file(DBName);
        std::string Pair;
        while(getline(file, Pair)) {
            DataBaseP[Pair.substr(0,Pair.size()- Pair.find(sep)-1)] = Pair.substr(Pair.find(sep)+1);
            //DataBaseP.insert(make_pair(Pair, Pair));
        }
        file.close();
    }
    std::map <std::string,std::string> DataBaseP;
    bool IDcheck(std::string login)
    {
        try {
            std::string Id = DataBaseP.at(login);
        } catch (std::out_of_range) {
            return false;
        }
        return true;
    }
};

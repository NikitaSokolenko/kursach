#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ErrorTracker.h"

extern ErrorTracker ErrTr;

class DB
{
private:
    char sep = ' ';
public:
    DB(std::string DBName)
    {
	try{
        std::ifstream file(DBName);
        std::string Pair;
        while(getline(file, Pair)) {
            DataBaseP[Pair.substr(0,Pair.find(sep))] = Pair.substr(Pair.find(sep)+1);
        }
        file.close();
		}catch (std::exception& e){
		ErrTr.write_log(e.what(), false);
	}
    }
    std::map <std::string,std::string> DataBaseP;
    bool IDcheck(std::string login)
    {
        for (std::map<std::string, std::string>::iterator it=DataBaseP.begin(); it!=DataBaseP.end(); ++it) {
            std::cout << it->first << " => " << it->second << '\n';
        }
		try{
			if (DataBaseP.count(login) != 1){
				throw std::invalid_argument(std::string("Invalid ID"));}
		}catch (std::exception& e){
			ErrTr.write_log(e.what(), false);
			return false;		
		}
        return DataBaseP.count(login) == 1;
    }
};

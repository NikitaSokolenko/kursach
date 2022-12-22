#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>
#include <iostream>
#include <boost/algorithm/string.hpp>

class DB: private ErrorTracker
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
            //DataBaseP.insert(make_pair(Pair, Pair));
        }
        file.close();
		}catch (std::exception& e){
		write_log(e.what(), false);
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
			std::cout<<"it here"<<std::endl;
			write_log(e.what(), false);		
		}
        return DataBaseP.count(login) == 1;
    }
};

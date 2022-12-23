#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include "ErrorTracker.h"


class Counter
{
private:
int16_t result[1];
public:
    Counter(){};
    int16_t * mean(std::vector<int16_t> arr)
    {
		try{
    	for (std::vector<int16_t>::iterator it = arr.begin() ; it != arr.end(); ++it){
    	std::cout << ' ' << *it;}
  		std::cout << '\n';
        double avg = 0;
        for (uint32_t i = 0; i < arr.size(); i++) {
            avg += (arr[i] - avg) / (i + 1);
        }
        result[0] = avg;
		}catch(std::exception &e){
			throw server_error(std::string("Invalid ID"), true);
			exit(1);}									
        return result;
    }
};
